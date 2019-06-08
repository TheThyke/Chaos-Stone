bool ChaosStoneLoad();
void ChaosStoneRespawnTimer();
void ChaosStoneSummon(uint16 ChaosGetID,uint8 RankID,uint16 ZoneID);
uint8 ChaosStoneSummonSelectStage(uint16 ChaosGetID, uint8 RankID, uint16 ZoneID);
uint8 ChaosStoneSummonSelectFamilyStage(uint16 ChaosGetID, uint8 FamilyID, uint16 ZoneID);
void	ChaosStoneDeath(CUser *pUser);
void	ChaosStoneBossKilledBy();
uint8	ChaosStoneSelectStage(uint8 sRank);
void    ChaosStoneDeathRespawnMonster(uint16 ChaosGetIndex);
