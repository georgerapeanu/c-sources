import requests;

def getRover(mapName):
    resp = requests.get("https://rover.codingcontest.org/rover/create?map=" + str(mapName) + "&username=georgerapeanu2&contestId=practice");
    return str(resp.text);

def readRover(uid):
    resp = requests.get("https://rover.codingcontest.org/rover/" + str(uid));
    return str(resp.text);

def moveRover(uid,distance,steeringAngle):
    resp = requests.get("https://rover.codingcontest.org/rover/move/" + str(uid) + "?distance=" + str(distance) + "&steeringAngle=" + str(steeringAngle));
    return str(resp.text);

def getSensors(uid):
    resp = requests.get("https://rover.codingcontest.org/rover/sensor/" + str(uid));
    return str(resp.text);

