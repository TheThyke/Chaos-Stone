if (pNpc->GetZoneID() == ZONE_RONARK_LAND
  || pNpc->GetZoneID() == ZONE_RONARK_LAND_BASE
  || pNpc->GetZoneID() == ZONE_ARDREAM)
{
  if (NpcAddSignalling->m_ChaosStoneChaosID > 0)
  {
    _CHAOS_STONE_INFO* pChaosInfo = g_pMain->m_ChaosStoneInfoArray.GetData(NpcAddSignalling->m_ChaosStoneChaosID);
    if (pChaosInfo != nullptr)
    {
      if (pNpc->GetZoneID() == pChaosInfo->sZoneID && pChaosInfo->isChaosStoneKilled == true && pNpc->isMonster())
      {
        if (pChaosInfo->sBoosID[0] == 0)
          pChaosInfo->sBoosID[0] = pNpc->GetID();
        else if (pChaosInfo->sBoosID[1] == 0)
          pChaosInfo->sBoosID[1] = pNpc->GetID();
        else if (pChaosInfo->sBoosID[2] == 0)
          pChaosInfo->sBoosID[2] = pNpc->GetID();
        else if (pChaosInfo->sBoosID[3] == 0)
          pChaosInfo->sBoosID[3] = pNpc->GetID();
        else if (pChaosInfo->sBoosID[4] == 0)
          pChaosInfo->sBoosID[4] = pNpc->GetID();
        else if (pChaosInfo->sBoosID[5] == 0)
          pChaosInfo->sBoosID[5] = pNpc->GetID();
        else if (pChaosInfo->sBoosID[6] == 0)
          pChaosInfo->sBoosID[6] = pNpc->GetID();

        pChaosInfo->sBoosKilledCount++;
      }
    }
  }
}
