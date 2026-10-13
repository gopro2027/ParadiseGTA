// Paradise RTM: queues commands for a menu through gtartm.php.
// Command format: functionid;param;param;...;  (spaces and ';' inside strings become ',')

let RTMKey = '';
let onResponse = (text) => alert(text);

function getRTMKey() {
  return RTMKey;
}
function setRTMKey(val) {
  RTMKey = val;
}
function setResponseHandler(fn) {
  onResponse = fn;
}

function sendData(text) {
  const url = '/rtm/gtartm.php?setData=true&RTMKey=' + encodeURIComponent(RTMKey) + '&RTMData=' + encodeURIComponent(text);
  fetch(url)
    .then((r) => r.text())
    .then(onResponse)
    .catch(() => onResponse('Could not reach the server'));
}

function executeFunction(functionid, ...parameters) {
  let text = functionid + ';';
  for (const o of parameters) {
    if (typeof o === 'string') text += o.replace(/ /g, ',').replace(/;/g, ',') + ';';
    else text += o + ';';
  }
  sendData(text);
}

function nullFunction() { executeFunction(0); }
function dialog(text) { executeFunction(1, text); }
function teleportPlayer(name, x, y, z) { executeFunction(2, name, x, y, z); }
function spawnVehicle(name, vehicleName) { executeFunction(3, name, vehicleName); }
function killPlayerAnonymous(name) { executeFunction(4, name); }
function killPlayer(name, killer) { executeFunction(5, name, killer); } // makes killer kill name
function moneyDrop(name, mode) { executeFunction(6, name, mode); } // 0 off, 1 on, 2 toggle
function spawnObjectXYZ(objectName, x, y, z) { executeFunction(7, objectName, x, y, z); }
function spawnObjectOnPlayerWithOffset(objectName, x, y, z, playerName) { executeFunction(8, objectName, x, y, z, playerName); }
function teleportPlayerToPlayer(name, playerToTeleportTo) { executeFunction(9, name, playerToTeleportTo); }
function setPlayerRank(name, rank) { executeFunction(10, name, rank); }
function playerAnimation(name, animationDictionary, animationName) { executeFunction(11, name, animationDictionary, animationName); }
function clearTask(name) { executeFunction(12, name); }
function setStat(name, statHash, value) { executeFunction(14, name, statHash, value); }
function removeWantedLevel(name) { executeFunction(15, name); }
function sendText(name, message) { executeFunction(16, name, message); }
function kickPlayer(name) { executeFunction(17, name); }
