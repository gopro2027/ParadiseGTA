#define SYSCALLS_UNAVAILABLE    0xFFFFFFFF80010003ULL

#define MAX_BLOCKED_URL         64

u64 blocked_url[MAX_BLOCKED_URL][2]; u8 url_count = 0;

#ifdef REMOVE_SYSCALLS

#ifdef PS3MAPI

static u64 sc_backup[CFW_SYSCALLS];

static void backup_cfw_syscalls(void)
{
	for(u8 sc = 0; sc < CFW_SYSCALLS; sc++)
		sc_backup[sc] = peekq( SYSCALL_PTR(sc_disable[sc]) );
}

static void restore_cfw_syscalls(void)
{
	if(!syscalls_removed) return;

	{ PS3MAPI_ENABLE_ACCESS_SYSCALL8 }

	{ system_call_2(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_DISABLE_COBRA, 0);}

	{ system_call_3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_PDISABLE_SYSCALL8, 0); }

	for(u8 sc = 0; sc < CFW_SYSCALLS; sc++)
		pokeq( SYSCALL_PTR(sc_disable[sc]), sc_backup[sc] );

	//ps3mapi_key = 0;
	{ PS3MAPI_ENABLE_ACCESS_SYSCALL8 }

	syscalls_removed = false;
}

#endif // #ifdef PS3MAPI

static void restore_blocked_urls(void)
{
	// restore blocked servers (XMB only)
	if(IS_ON_XMB) {for(u8 u = 0; u<url_count; u++) poke_lv1(blocked_url[u][0], blocked_url[u][1]); url_count = 0;}
}

static void remove_cfw_syscall8(void)
{
	if(!SYSCALL_TABLE) return;

	#ifdef COBRA_ONLY
	{ PS3MAPI_ENABLE_ACCESS_SYSCALL8 }
	#endif

	restore_blocked_urls();

	u64 sc_null = peekq(SYSCALL_TABLE), toc = peekq(TOC);

	// disable syscall 8 only if others cfw syscalls were disabled
	if(syscalls_removed || toc == SYSCALLS_UNAVAILABLE || toc == sc_null)
	{
		#ifdef COBRA_ONLY
		{ system_call_3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_PDISABLE_SYSCALL8, 0); }
		{ system_call_3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_DISABLE_SYSCALL, SC_COBRA_SYSCALL8); }
		#endif

		pokeq(SYSCALL_PTR( SC_COBRA_SYSCALL8 ), sc_null);
	}
}

static void remove_cfw_syscalls(bool keep_ccapi)
{
	detect_firmware();

	if(!SYSCALL_TABLE || syscalls_removed) return;

	u64 sc_null = peekq(SYSCALL_TABLE);

	u32 initial_sc = keep_ccapi ? 5 : 0;

	#ifdef COBRA_ONLY
	for(u8 sc = initial_sc; sc < CFW_SYSCALLS; sc++)
	{ system_call_3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_DISABLE_SYSCALL, (u64)sc_disable[sc]); }
	{ system_call_3(SC_COBRA_SYSCALL8, SYSCALL8_OPCODE_PS3MAPI, PS3MAPI_OPCODE_PDISABLE_SYSCALL8, webman_config->sc8mode); } // default: Partial disable syscall8 (Keep cobra/mamba+ps3mapi features only)

	if(webman_config->sc8mode == 4) remove_cfw_syscall8();
	#endif

	for(u8 sc = initial_sc; sc < CFW_SYSCALLS; sc++)
		pokeq(SYSCALL_PTR( sc_disable[sc] ), sc_null);

	u64 sc9  = peekq(SYSCALL_PTR( 9));

	syscalls_removed = (sc9 == SYSCALLS_UNAVAILABLE || sc9 == sc_null);
/*
	#ifdef COBRA_ONLY
	if(syscalls_removed)
	{
		CellRtcTick mTick; cellRtcGetCurrentTick(&mTick);
		ps3mapi_key = mTick.tick; for(u16 r = 0; r < (ps3mapi_key & 0xFFF) + 0xF; r++) {ps3mapi_key = ((ps3mapi_key<<15) ^ (ps3mapi_key>>49)) ^ (ps3mapi_key + 1);}
	}
	#endif
*/
}

static void disable_cfw_syscalls(bool keep_ccapi)
{
	{ PS3MAPI_ENABLE_ACCESS_SYSCALL8 }

	if(syscalls_removed)
	{
		{ BEEP2 }
		show_msg((char*)STR_CFWSYSALRD);
	}
	else
	{
#ifndef ENGLISH_ONLY
		char STR_CFWSYSRIP[128];//	= "Removal History files & CFW Syscalls in progress...";
		char STR_RMVCFWSYS[136];//	= "History files & CFW Syscalls deleted OK!";
		char STR_RMVCFWSYSF[80];//	= "Failed to remove CFW Syscalls";

		language("STR_CFWSYSRIP", STR_CFWSYSRIP, "Removal History files & CFW Syscalls in progress...");
		language("STR_RMVCFWSYS", STR_RMVCFWSYS, "History files & CFW Syscalls deleted OK!");
		language("STR_RMVCFWSYSF", STR_RMVCFWSYSF, "Failed to remove CFW Syscalls");

		close_language();
#endif
		show_msg((char*)STR_CFWSYSRIP);
		remove_cfw_syscalls(keep_ccapi);
		delete_history(true);

		if(syscalls_removed)
		{
			{ BEEP1 }
			show_msg((char*)STR_RMVCFWSYS);
		}
		else
		{
			{ BEEP2 }
			show_msg((char*)STR_RMVCFWSYSF);
		}
	}

	sys_ppu_thread_sleep(2);

	{ PS3MAPI_DISABLE_ACCESS_SYSCALL8 }
}

#endif // #ifdef REMOVE_SYSCALLS

static bool block_url(u64 addr, u64 value)
{
	if(url_count>=MAX_BLOCKED_URL) return false;

	// backup original value @ poke address
	blocked_url[url_count][0] = addr;
	blocked_url[url_count][1] = peek_lv1(addr);

	poke_lv1(addr, value);

	url_count++, addr += 0x20;

	return true;
}

static void block_online_servers(bool notify)
{
	if(url_count == 0)
	{
		if(IS_INGAME) return; // not in XMB

		if(notify) show_msg((char*)"Blocking PSN servers");

		{ PS3MAPI_ENABLE_ACCESS_SYSCALL8 }

		{ PS3MAPI_REENABLE_SYSCALL8 }

		if(peekq(TOC) == SYSCALLS_UNAVAILABLE)
		{
			show_msg((char*)STR_CFWSYSALRD);
		}
		else
		{
			led(YELLOW, BLINK_FAST);

			u64 mem = 0; u8 pcount = 0;

			// LV1

			for(u64 addr = 0x880000; addr < 0xE1FFFFULL; addr += 4)//16MB
			{
				mem = peek_lv1(addr);

				if(     mem == 0x733A2F2F61757468ULL)  // s://auth
					{if(!block_url(addr,   0x733A2F2F00000000ULL)) break;}
				else if(mem == 0x2E7073332E757064ULL)  // .ps3.upd
					{if(!block_url(addr-8, 0x3A2F2F0000000000ULL)) break;}
				else if(mem == 0x656E612E6E65742EULL)  // ena.net.
					{if(!block_url(addr,   0x0000000000000000ULL)) break;}
				else if(mem == 0x687474703A2F2F70ULL)  // http://p
					{if(!block_url(addr,   0x687474703A2F2F00ULL)) break; pcount++; if(pcount>=44) break;}
			}

			// LV2
			u64 start_addr = 0x300000ULL + LV2_OFFSET_ON_LV1, stop_addr = 0x7FFFF8ULL + LV2_OFFSET_ON_LV1;

			for(u64 addr = start_addr; addr < stop_addr; addr += 4)//8MB
			{
				mem = peek_lv1(addr);
				if(     mem == 0x733A2F2F6E73782EULL)   // s://nsx.
					{if(!block_url(addr,   0x733A2F2F00000000ULL)) break;}
				else if(mem == 0x3A2F2F6E73782D65ULL)   // ://nsx-e
					{if(!block_url(addr,   0x3A2F2F0000000000ULL)) break;}
				else if(mem == 0x3A2F2F786D622D65ULL)   // ://xmb-e
					{if(!block_url(addr,   0x3A2F2F0000000000ULL)) break;}
				else if(mem == 0x2E7073332E757064ULL)   // .ps3.upd
					{if(!block_url(addr-8, 0x3A2F2F0000000000ULL)) break;}
				else if(mem == 0x702E616470726F78ULL)   // p.adprox
					{if(!block_url(addr-8, 0x733A2F2F00000000ULL)) break;}
				else if(mem == 0x656E612E6E65742EULL)   // ena.net.
					{if(!block_url(addr,   0x0000000000000000ULL)) break;}
				else if(mem == 0x702E7374756E2E70ULL)   // p.stun.p
					{if(!block_url(addr-4, 0x0000000000000000ULL)) break;}
				else if(mem == 0x2E7374756E2E706CULL)   // .stun.pl
					{if(!block_url(addr-4, 0x0000000000000000ULL)) break;}
				//else if(mem == 0x63726565706F2E77ULL)   // creepo.w
				//	{if(!block_url(addr,   0x0000000000000000ULL)) break;}
			}

			led(YELLOW, OFF);

			led(GREEN, ON);
		}

		{ PS3MAPI_RESTORE_SC8_DISABLE_STATUS }

		{ PS3MAPI_DISABLE_ACCESS_SYSCALL8 }
	}

	if(notify)
	{
		if(url_count > 0) show_msg((char*)"PSN servers blocked");
	}
}
