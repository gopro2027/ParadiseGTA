/* kurt2467*/

struct Native_s
{	
	Native_s*	LastNativesTable;
	unsigned int 	NativeFunctions[7];
	unsigned int 	NativeCount;
	unsigned int 	NativeHashes[7];
};

struct NativeArg_s
{
	int* ReturnValue;
	unsigned int ArgCount;
	ScriptArg* ArgValues;
	unsigned int ReadCount;
};

extern Native_s** g_Natives;
static NativeArg_s* NativeArg = (NativeArg_s*)0x10060000; //Open space addr

void ResetArgs()
{
	NativeArg->ArgCount = 0;
	NativeArg->ReadCount = 0;
	NativeArg->ArgValues = (ScriptArg*)0x10050000;
	NativeArg->ReturnValue = (int*)NativeArg->ArgValues;
}
template<typename T>
void PushArg(T Value)
{
	*(T*)&NativeArg->ArgValues[NativeArg->ArgCount] = Value;
	NativeArg->ArgCount++;
}
template<typename R>
R GetReturn()
{
	R* Result;
	Result = (R*)&NativeArg->ReturnValue[0];
	return *(R*)Result;
}
void CallHash(unsigned int hash, NativeArg_s* pArg) 
{
	Native_s* Natives = ((Native_s**)(addrstruct().nativeTable^dataDecryptor()))/*g_Natives*/[hash & 0xFF];
	while (Natives != 0)
	{
		for (unsigned int i = 0; i < Natives->NativeCount; i++)
		{
			if (Natives->NativeHashes[i] == hash)
			{
				((void(*)(NativeArg_s*))Natives->NativeFunctions[i])(pArg);
				return;
			}
		}
		Natives = Natives->LastNativesTable;
	}
}

int getOPDOfNative(unsigned int hash)
{
	//printf("Here\n");
	Native_s* Natives = ((Native_s**)(addrstruct().nativeTable ^ dataDecryptor()))/*g_Natives*/[hash & 0xFF];
	//printf("dere 0x%X\n",Natives);
	while (Natives != 0)
	{
		for (unsigned int i = 0; i < Natives->NativeCount; i++)
		{
			if (Natives->NativeHashes[i] == hash)
			{
				//Natives->NativeFunctions[i] is opd I think
				//printf("Wii\n");
				int address = (int)(Natives->NativeFunctions[i]);
				//printf("Native 0x%X had address 0x%X\n",hash,address);
				//((void(*)(NativeArg_s*))Natives->NativeFunctions[i])(pArg);
				return address;
			}
		}
		Natives = Natives->LastNativesTable;
	}
	printf("Invalid return!\n");
	return -1;
}

#if oldInvoke == 1
template<typename T>
T invoke(unsigned int NativeHash)
{
	ResetArgs();
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1>
T invoke(unsigned int NativeHash, P1 p0)
{
	ResetArgs();
	PushArg(p0);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2>
T invoke(unsigned int NativeHash, P1 p0, P2 p1)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14, P16 p15)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	PushArg(p15);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14, P16 p15, P17 p16)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	PushArg(p15);
	PushArg(p16);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14, P16 p15, P17 p16, P18 p17)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	PushArg(p15);
	PushArg(p16);
	PushArg(p17);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14, P16 p15, P17 p16, P18 p17, P19 p18)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	PushArg(p15);
	PushArg(p16);
	PushArg(p17);
	PushArg(p18);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14, P16 p15, P17 p16, P18 p17, P19 p18, P20 p19)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	PushArg(p15);
	PushArg(p16);
	PushArg(p17);
	PushArg(p18);
	PushArg(p19);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14, P16 p15, P17 p16, P18 p17, P19 p18, P20 p19, P21 p20)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	PushArg(p15);
	PushArg(p16);
	PushArg(p17);
	PushArg(p18);
	PushArg(p19);
	PushArg(p20);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14, P16 p15, P17 p16, P18 p17, P19 p18, P20 p19, P21 p20, P22 p21)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	PushArg(p15);
	PushArg(p16);
	PushArg(p17);
	PushArg(p18);
	PushArg(p19);
	PushArg(p20);
	PushArg(p21);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14, P16 p15, P17 p16, P18 p17, P19 p18, P20 p19, P21 p20, P22 p21, P23 p22)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	PushArg(p15);
	PushArg(p16);
	PushArg(p17);
	PushArg(p18);
	PushArg(p19);
	PushArg(p20);
	PushArg(p21);
	PushArg(p22);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14, P16 p15, P17 p16, P18 p17, P19 p18, P20 p19, P21 p20, P22 p21, P23 p22, P24 p23)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	PushArg(p15);
	PushArg(p16);
	PushArg(p17);
	PushArg(p18);
	PushArg(p19);
	PushArg(p20);
	PushArg(p21);
	PushArg(p22);
	PushArg(p23);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14, P16 p15, P17 p16, P18 p17, P19 p18, P20 p19, P21 p20, P22 p21, P23 p22, P24 p23, P25 p24)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	PushArg(p15);
	PushArg(p16);
	PushArg(p17);
	PushArg(p18);
	PushArg(p19);
	PushArg(p20);
	PushArg(p21);
	PushArg(p22);
	PushArg(p23);
	PushArg(p24);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}

template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5, typename P6, typename P7, typename P8, typename P9, typename P10, typename P11, typename P12, typename P13, typename P14, typename P15, typename P16, typename P17, typename P18, typename P19, typename P20, typename P21, typename P22, typename P23, typename P24, typename P25, typename P26>
T invoke(unsigned int NativeHash, P1 p0, P2 p1, P3 p2, P4 p3, P5 p4, P6 p5, P7 p6, P8 p7, P9 p8, P10 p9, P11 p10, P12 p11, P13 p12, P14 p13, P15 p14, P16 p15, P17 p16, P18 p17, P19 p18, P20 p19, P21 p20, P22 p21, P23 p22, P24 p23, P25 p24, P26 p25)
{
	ResetArgs();
	PushArg(p0);
	PushArg(p1);
	PushArg(p2);
	PushArg(p3);
	PushArg(p4);
	PushArg(p5);
	PushArg(p6);
	PushArg(p7);
	PushArg(p8);
	PushArg(p9);
	PushArg(p10);
	PushArg(p11);
	PushArg(p12);
	PushArg(p13);
	PushArg(p14);
	PushArg(p15);
	PushArg(p16);
	PushArg(p17);
	PushArg(p18);
	PushArg(p19);
	PushArg(p20);
	PushArg(p21);
	PushArg(p22);
	PushArg(p23);
	PushArg(p24);
	PushArg(p25);
	CallHash(NativeHash, NativeArg);
	return GetReturn<T>();
}
#else







/*
#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,_64,_65,_66,_67,_68,_69,_70, \
         _71,_72,_73,_74,_75,_76,_77,_78,_79,_80, \
         _81,_82,_83,_84,_85,_86,_87,_88,_89,_90, \
         _91,_92,_93,_94,_95,_96,_97,_98,_99,_100, \
         _101,_102,_103,_104,_105,_106,_107,_108,_109,_110, \
         _111,_112,_113,_114,_115,_116,_117,_118,_119,_120, \
         _121,_122,_123,_124,_125,_126,_127,N,...) N
#define PP_RSEQ_N() \
         127,126,125,124,123,122,121,120, \
         119,118,117,116,115,114,113,112,111,110, \
         109,108,107,106,105,104,103,102,101,100, \
         99,98,97,96,95,94,93,92,91,90, \
         89,88,87,86,85,84,83,82,81,80, \
         79,78,77,76,75,74,73,72,71,70, \
         69,68,67,66,65,64,63,62,61,60, \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

//template <typename T>
#define invoke<T>(...) _invoke<T>(PP_NARG(__VA_ARGS__), __VA_ARGS__)
*/

static inline unsigned int floatparam (float f) {
  union { unsigned int u; float f; } u;
  u.f = f;
  return u.u;
}

template <typename T>
T invoke(int n, unsigned int NativeHash, ...) {
	//int n = 26;//arg count
	ResetArgs();
	va_list vl;
	va_start(vl,n);

	//unsigned int NativeHash = va_arg(vl,unsigned int);
	printf("In call! %i 0x%X\n",n,NativeHash);
	for (int i=0;i<n;i++) {
		printf("g");
		unsigned int val = va_arg(vl,unsigned int);
		printf("b");
		PushArg(val);
		printf("a\n");
	}
	printf("end.");
	va_end(vl);
	printf("ended\n");
	CallHash(NativeHash, NativeArg);
	printf("called\n");
	return GetReturn<T>();
}

#endif