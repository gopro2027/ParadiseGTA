// GTA V (PS3) addresses/values the SPRX needs at startup, sent by connecq.php in this exact order.
// They used to be XOR encrypted per session; they are now sent as plain numbers.
// Order must match the getNextData() calls in testSocket() (ParadiseGTA_optimized_2020/Networking.h)
// and struct Addresses in prx.cpp.
export const OFFSETS = [
  ['nativeTable', 0x1E6FF38],
  ['cashDropFix', 0x003FA510],
  ['scriptBypass', 0x01306254],
  ['teleportPlayerCallback', 0x1C6BF80],
  ['objectBypass', 0x3F8B84],
  ['modelToHash', 0x9D9830],
  ['entityToIndex', 0x474054],
  ['getCNetGamePlayer', 0x47E00C],
  ['getEntityAttachedTo', 0x3A9EFC],
  ['hookP1', 0x3D600000], // lis %r11, dest>>16
  ['hookP2', 0x396B0000], // addi %r11, %r11, dest&0xFFFF
  ['hookP3', 0x7D6903A6], // mtctr %r11
  ['hookP4', 0x4E800420], // bctr
  ['textData', 0x27A244D8],
  ['hookAddress', 0x3E3A20],
  ['NETWORK_CREATE_SYNCHRONISED_SCENE', 0xB06FE3FE],
  ['quadAddress', 0xDD2BFC77],
  ['entityFromIndex', 0xA552E0],
  ['devmode', 'DEVMODE'], // 1 for dev keys, 0 otherwise
  ['allClientStatsAddress', 0x13AE3B0],
  ['FCWfuncAddress', 'DEV', 0x12C2ECC], // the FCW values are only sent to dev keys
  ['FCWarg0', 'DEV', 1],
  ['FCWarg1', 'DEV', 0xE],
  ['FCWarg2', 'DEV', 0x2148E84],
  ['FCWarg3', 'DEV', 0xD04],
  ['setPlayerTeamAddr', 0x08421B34],
  ['getPlayerIdAddr', 0x4241D4],
  ['setSCTVSlotsAddr', 0x043E4298],
  ['setPlayerTeamAddr2', 0x159A284],
  ['antiFreezeAddr1', 0x1C707E0],
  ['antiFreezeAddr2', 0x133C430],
  ['renderResulutionParams', 0x1DE12C0],
  ['stringDecryptHash', 0], // no longer used
  ['SCEventTicketFunc', 0xD38374],
  ['SCEventAnotherFunc', 0xD6DC10],
  ['PedProtVal1', 0x1C72E70],
  ['PedProtVal2', 0x13CA768],
  ['temporaryTimeVal', 'TIME'],
  ['privk0', 0x183D82],
  ['privk1', 0x14122C],
  ['privk2', 0x18396D],
  ['privk3', 0x1CC4A34],
  ['privk4', 0xA8B814],
  ['privk5', 0xA8B908],
  ['privk6', 0x1EC6980],
  ['privk7', 0x1626844],
  ['privk8', 0xA8B5FC],
  ['privk9', 0xA8BBBC],
  ['privk10', 0xA8B978],
  ['privk11', 0x9F8FF0],
  ['privk12', 0x1888BD0],
  ['privk13', 0x1894210],
  ['privk14', 0x51BA0],
  ['privk15', 0x1888BE0],
  ['privk16', 0x150BAA4],
  ['privk17', 0x1EC672C],
  ['privk18', 0x1CC57B8],
  ['privk19', 0x1EC69C0],
  ['suggest', 0x9FC1F4],
  ['privk_132AE30', 0x132AE30],
];

export function offsetValues({ dev = false, now = Math.floor(Date.now() / 1000) } = {}) {
  return OFFSETS.map(([, a, b]) => {
    if (a === 'DEVMODE') return dev ? 1 : 0;
    if (a === 'TIME') return now;
    if (a === 'DEV') return dev ? b : 0;
    return a;
  });
}

// each value is an unsigned decimal number right padded with spaces to 20 characters
export function formatField(value) {
  return String(value >>> 0).padEnd(20, ' ');
}
