#include "stdafx.h"
#include "DBAgent.h"

using std::string;
using std::unique_ptr;

bool CGameServerDlg::ChaosStoneLoad()
{
	uint8 ChaosStoneResCount = 0;
	if (g_pMain->ChaosStoneRespawnOkey 
		&& g_pMain->m_ChaosStoneRespawnCoordinateArray.GetSize() > 0)
	{
		for (int i = 1; i <= g_pMain->m_ChaosStoneRespawnCoordinateArray.GetSize(); i++)
		{
			_CHAOS_STONE_RESPAWN *pChaosRespawn = g_pMain->m_ChaosStoneRespawnCoordinateArray.GetData(i);
			if (pChaosRespawn == nullptr
				|| pChaosRespawn->sRank != 1)
				continue;

			ChaosStoneResCount++;
			if (ChaosStoneResCount > 3)
				return false;

			_CHAOS_STONE_INFO* pChaosInfo = g_pMain->m_ChaosStoneInfoArray.GetData(ChaosStoneResCount);
			if (pChaosInfo == nullptr)
				return false;

			pChaosInfo->sChaosID = pChaosRespawn->sChaosID;
			pChaosInfo->sRank = pChaosRespawn->sRank;
			pChaosInfo->sZoneID = pChaosRespawn->sZoneID;
			pChaosInfo->sSpawnTime = pChaosRespawn->sSpawnTime;
			pChaosInfo->sMonsterFamily = 1;
			pChaosInfo->isChaosStoneKilled = false;
			pChaosInfo->isOnResTimer = false;
			pChaosInfo->isTotalKilledMonster = false;
			pChaosInfo->ChaosStoneON = true;
			
			g_pMain->SpawnEventNpc(pChaosRespawn->sChaosID, true, (uint8)pChaosRespawn->sZoneID, pChaosRespawn->sSpawnX, 0, pChaosRespawn->sSpawnZ, pChaosRespawn->sCount, pChaosRespawn->sRadiusRange, 0, 0, -1, 0, (uint8)pChaosRespawn->sDirection);
			printf("Chaos Stone:ID(%d),Zone(%d) ON.\n", pChaosRespawn->sChaosID, pChaosRespawn->sZoneID);
		}
		g_pMain->ChaosStoneRespawnOkey = false;
	}
	return true;
}

void CGameServerDlg::ChaosStoneRespawnTimer()
{
	if (g_pMain->m_ChaosStoneInfoArray.GetSize() > 0)
	{
		for (int i = 1; i <= g_pMain->m_ChaosStoneInfoArray.GetSize(); i++)
		{
			_CHAOS_STONE_INFO* pChaosInfo = g_pMain->m_ChaosStoneInfoArray.GetData(i);
			if (pChaosInfo == nullptr)
			{
				printf("Chaos Stone ID (%d) Error Timer\n", pChaosInfo->sChaosID);
					continue;
			}

			if (!pChaosInfo->ChaosStoneON
				|| !pChaosInfo->isOnResTimer
				|| !pChaosInfo->isChaosStoneKilled
				|| !pChaosInfo->isTotalKilledMonster)
				continue;

			if (pChaosInfo->sSpawnTime > 0)
				pChaosInfo->sSpawnTime--;

			if (pChaosInfo->sSpawnTime <= 0)
			{
				ChaosStoneSummon(pChaosInfo->sChaosID, pChaosInfo->sRank, pChaosInfo->sZoneID);
				pChaosInfo->isChaosStoneKilled = false;
				pChaosInfo->isOnResTimer = false;
				pChaosInfo->isTotalKilledMonster = false;
			}
		}
	}
}
//THETHYKE

uint8 CGameServerDlg::ChaosStoneSummonSelectStage(uint16 ChaosGetID, uint8 RankID, uint16 ZoneID)
{
	for (int i = 1; i <= g_pMain->m_ChaosStoneInfoArray.GetSize(); i++)
	{
		_CHAOS_STONE_INFO* pChaosInfo = g_pMain->m_ChaosStoneInfoArray.GetData(i);
		if (pChaosInfo == nullptr)
		{
			printf("Chaos Stone ID (%d) Error Timer (2)\n", pChaosInfo->sChaosID);
			continue;
		}

		if (pChaosInfo->sChaosID == ChaosGetID && pChaosInfo->sRank == RankID && pChaosInfo->sZoneID == ZoneID)
			return (uint8)pChaosInfo->sChaosIndex;
	}

	return 0;
}

void CGameServerDlg::ChaosStoneSummon(uint16 ChaosGetID,uint8 RankID, uint16 ZoneID)
{
	if (g_pMain->m_ChaosStoneRespawnCoordinateArray.GetSize() > 0)
	{
		for (int i = 1; i <= g_pMain->m_ChaosStoneRespawnCoordinateArray.GetSize(); i++)
		{
			_CHAOS_STONE_RESPAWN *pChaosRespawn = g_pMain->m_ChaosStoneRespawnCoordinateArray.GetData(i);
			if (pChaosRespawn == nullptr
				|| pChaosRespawn->sChaosID != ChaosGetID
				|| pChaosRespawn->sRank != RankID
				|| pChaosRespawn->sZoneID != ZoneID)
				continue;

			uint8 Info = ChaosStoneSummonSelectStage(pChaosRespawn->sChaosID,pChaosRespawn->sRank,pChaosRespawn->sZoneID);
			_CHAOS_STONE_INFO* pChaosInfo = g_pMain->m_ChaosStoneInfoArray.GetData(Info);
			if (pChaosInfo == nullptr)
				continue;

			g_pMain->SpawnEventNpc(pChaosRespawn->sChaosID, true, (uint8)pChaosRespawn->sZoneID, pChaosRespawn->sSpawnX, 0, pChaosRespawn->sSpawnZ, pChaosRespawn->sCount, pChaosRespawn->sRadiusRange, 0, 0, -1, 0, (uint8)pChaosRespawn->sDirection);
			pChaosInfo->sSpawnTime = pChaosRespawn->sSpawnTime;
		}
	}
}

uint8 CNpc::ChaosStoneSelectStage(uint8 sRank)
{
	if (g_pMain->m_ChaosStoneRespawnCoordinateArray.GetSize() > 0)
	{
		for (int i = 1; i <= g_pMain->m_ChaosStoneRespawnCoordinateArray.GetSize(); i++)
		{
			_CHAOS_STONE_RESPAWN *pChaosRespawn = g_pMain->m_ChaosStoneRespawnCoordinateArray.GetData(i);
			if (pChaosRespawn == nullptr)
			{
				printf("Chaos Stone ID (%d) Error Select Stage\n", pChaosRespawn->sChaosID);
				continue;
			}

			if (pChaosRespawn->sChaosID == GetProtoID() && pChaosRespawn->sRank == sRank && pChaosRespawn->sZoneID && GetZoneID())
				return (uint8)pChaosRespawn->sIndex;
			else if (pChaosRespawn->sChaosID == GetProtoID() && pChaosRespawn->sRank == 1 && pChaosRespawn->sZoneID && GetZoneID())
				return (uint8)pChaosRespawn->sIndex;
		}
	}
	return 0;
}

void CNpc::ChaosStoneDeath(CUser *pUser)
{
	if (pUser == nullptr)
		return;

	g_pMain->SendNotice<CHAOS_STONE_ENEMY_NOTICE>("", GetZoneID(), Nation::ALL);
	uint8 ChaosIndex = 0;

	if (g_pMain->m_ChaosStoneInfoArray.GetSize() > 0)
	{
		for (int i = 1; i <= g_pMain->m_ChaosStoneInfoArray.GetSize(); i++)
		{
			_CHAOS_STONE_INFO* pChaosInfo = g_pMain->m_ChaosStoneInfoArray.GetData(i);
			if (pChaosInfo == nullptr 
				|| !pChaosInfo->ChaosStoneON
				|| pChaosInfo->sZoneID != GetZoneID()
				|| GetProtoID() != pChaosInfo->sChaosID)
			{
				printf("Chaos Stone Info Error Death (1)\n");
				continue;
			}

			pChaosInfo->sRank++;
			pChaosInfo->isChaosStoneKilled = true;
			uint8 Respawn = ChaosStoneSelectStage(pChaosInfo->sRank);

			_CHAOS_STONE_RESPAWN* pChaosRespawn = g_pMain->m_ChaosStoneRespawnCoordinateArray.GetData(Respawn);
			if (pChaosRespawn == nullptr)
			{
				printf("Chaos Stone ID (%d) Error Death\n",pChaosInfo->sChaosID);
				continue;
			}
				
			pChaosInfo->sSpawnTime = pChaosRespawn->sSpawnTime;
			pChaosInfo->sRank = pChaosRespawn->sRank;
			pChaosInfo->isOnResTimer = true;
			ChaosIndex = pChaosInfo->sChaosIndex;
			
		}
		g_pMain->ChaosStoneBoosRespawnOkey = true;
		ChaosStoneDeathRespawnMonster(ChaosIndex);
	}
}

void CNpc::ChaosStoneDeathRespawnMonster(uint16 ChaosGetIndex)
{
	_CHAOS_STONE_INFO* pChaosInfo = g_pMain->m_ChaosStoneInfoArray.GetData(ChaosGetIndex);
	if (pChaosInfo == nullptr)
	{
		printf("Chaos Stone Error Monster Respawn\n");
		return;
	}

	if (g_pMain->m_ChaosStoneSummonListArray.GetSize() > 0)
	{
		foreach_stlmap(itr, g_pMain->m_ChaosStoneSummonListArray)
		{
			_CHAOS_STONE_SUMMON_LIST* pSummonList = itr->second;
			if (pSummonList == nullptr)
				continue;

			if (pSummonList->ZoneID == pChaosInfo->sZoneID && pSummonList->MonsterSpawnFamily == pChaosInfo->sMonsterFamily)
			{
				
				g_pMain->SpawnEventNpc(pSummonList->sSid, true, GetZoneID(), GetX(), GetY(), GetZ(), 1, CHAOS_STONE_MONSTER_RESPAWN_RADIUS, CHAOS_STONE_MONSTER_LIVE_TIME, GetNation(), GetID(), GetEventRoom(), 0, 1, 0, 0, uint8(ChaosGetIndex));
			}
		}
		pChaosInfo->sMonsterFamily++;
		uint8 Family = g_pMain->ChaosStoneSummonSelectFamilyStage(pChaosInfo->sChaosID, pChaosInfo->sMonsterFamily, pChaosInfo->sZoneID);
		
		if (Family)
			pChaosInfo->sMonsterFamily = Family;
	}
}


uint8 CGameServerDlg::ChaosStoneSummonSelectFamilyStage(uint16 ChaosGetID, uint8 FamilyID, uint16 ZoneID)
{
	foreach_stlmap(itr, m_ChaosStoneStageArray)
	{
		_CHAOS_STONE_STAGE* pStageList = itr->second;
		if (pStageList == nullptr)
			continue;

		if (pStageList->ZoneID == ZoneID && pStageList->nIndexFamily == FamilyID)
			return pStageList->nIndexFamily;
		else if (pStageList->ZoneID == ZoneID && pStageList->nIndexFamily == 1)
			return pStageList->nIndexFamily;
	}

	return 1;
}


#pragma region CDBAgent::LoadChaosStoneFamilyStage()
bool CDBAgent::LoadChaosStoneFamilyStage()
{
	unique_ptr<OdbcCommand> dbCommand(m_GameDB->CreateCommand());

	if (dbCommand.get() == nullptr)
		return false;

	if (!dbCommand->Execute(_T("{CALL LOAD_CHAOS_STONE_STAGE}")))
	{
		ReportSQLError(m_GameDB->GetError());
		return false;
	}

	if (!dbCommand->hasData())
		return false;

	do
	{
		_CHAOS_STONE_STAGE *pData = new _CHAOS_STONE_STAGE;

		dbCommand->FetchByte(1, pData->nIndex);
		dbCommand->FetchUInt16(2, pData->ZoneID);
		dbCommand->FetchByte(3, pData->nIndexFamily);

		if (!g_pMain->m_ChaosStoneStageArray.PutData(pData->nIndex, pData))
			delete pData;

	} while (dbCommand->MoveNext());

	return true;
}
#pragma endregion
