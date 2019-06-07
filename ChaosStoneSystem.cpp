#include "stdafx.h"

bool CGameServerDlg::ChaosStoneLoad()
{
	uint8 ChaosStoneResCount = 0;
	if (g_pMain->ChaosStoneRespawnOkey 
		&& g_pMain->m_ChaosStoneRespawnCoordinateArray.GetSize() > 0)
	{
		for (int i = 1; i <= g_pMain->m_ChaosStoneRespawnCoordinateArray.GetSize(); i++)
		{
			_CHAOS_RESPAWN *pChaosRespawn = g_pMain->m_ChaosStoneRespawnCoordinateArray.GetData(i);
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
			pChaosInfo->ChaosStoneON = true;
			
			//--GÜNCELLEME--
			pChaosInfo->isChaosStoneKilled = false;
			pChaosInfo->isOnResTimer = false;
			pChaosInfo->isTotalKilledMonster = false;
			//--GÜNCELLEME--

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
			_CHAOS_RESPAWN *pChaosRespawn = g_pMain->m_ChaosStoneRespawnCoordinateArray.GetData(i);
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
			_CHAOS_RESPAWN *pChaosRespawn = g_pMain->m_ChaosStoneRespawnCoordinateArray.GetData(i);
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

			_CHAOS_RESPAWN* pChaosRespawn = g_pMain->m_ChaosStoneRespawnCoordinateArray.GetData(Respawn);
			if (pChaosRespawn == nullptr)
			{
				printf("Chaos Stone ID (%d) Error Death\n",pChaosInfo->sChaosID);
				continue;
			}
				
			pChaosInfo->sSpawnTime = pChaosRespawn->sSpawnTime;
			pChaosInfo->sRank = pChaosRespawn->sRank;
			pChaosInfo->isOnResTimer = true;
		}
	}
}

//