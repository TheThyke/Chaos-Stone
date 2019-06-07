struct _CHAOS_STONE_INFO
{
	uint8  sChaosIndex;
	uint16 sChaosID;
	uint16  sZoneID;
	uint8	sRank;
	uint32   sSpawnTime;
	bool isChaosStoneKilled;
	bool isTotalKilledMonster;
	bool isOnResTimer;
	bool ChaosStoneON;

	_CHAOS_STONE_INFO()
	{
		Initialize();
	}

	void Initialize()
	{
		sChaosIndex = 0;
		sChaosID = 0;
		sZoneID = 0;
		sRank = 1;
		sSpawnTime = 30;
		isChaosStoneKilled = false;
		isTotalKilledMonster = false;
		isOnResTimer = false;
		ChaosStoneON = false;
	}
};

struct _CHAOS_STONE_SUMMON_LIST
{
	uint32	nIndex;
	uint16	ZoneID;
	uint16	sSid;
	uint8	MonsterSpawnFamily;
};

struct _CHAOS_RESPAWN
{
	uint8	sIndex;
	uint16  sZoneID;
	uint8	sRank;
	uint16  sChaosID;
	uint16  sCount;
	uint16  sSpawnX;
	uint16  sSpawnZ;
	uint8   sSpawnTime;
	uint16  sDirection;
	uint16  sRadiusRange;
};
