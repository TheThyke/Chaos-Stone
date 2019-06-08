struct _CHAOS_STONE_INFO
{
	uint8  sChaosIndex;
	uint16 sChaosID;
	uint16 sZoneID;
	uint8  sRank;
	uint32 sSpawnTime;
	uint8  sMonsterFamily;
	uint16 sBoosID[9];
	uint8  sBoosKilledCount;
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
		memset(&sBoosID, 0, sizeof(sBoosID));
		sChaosIndex = 0;
		sChaosID = 0;
		sZoneID = 0;
		sRank = 1;
		sSpawnTime = 30;
		sMonsterFamily = 0;
		sBoosKilledCount = 0;
		isChaosStoneKilled = false;
		isTotalKilledMonster = false;
		isOnResTimer = false;
		ChaosStoneON = false;
	}
};

struct _CHAOS_STONE_BOOS_KILLED_INFO
{
	uint8 sNpcID[10];
	uint8  sNpcKilled;

	_CHAOS_STONE_BOOS_KILLED_INFO()
	{
		Initialize();
	}
	void Initialize()
	{
		memset(&sNpcID, 0, sizeof(sNpcID));
		sNpcKilled = 0;
	}
};

struct _CHAOS_STONE_SUMMON_LIST
{
	uint32	nIndex;
	uint16	ZoneID;
	uint16	sSid;
	uint8	MonsterSpawnFamily;
};

struct _CHAOS_STONE_RESPAWN
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

struct _CHAOS_STONE_STAGE
{
	uint8 nIndex;
	uint16 ZoneID;
	uint8 nIndexFamily;
};
