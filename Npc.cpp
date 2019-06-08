---OnDeathProcess---
if (GetProtoID() == CHAOS_STONE1 || GetProtoID() == CHAOS_STONE2 || GetProtoID() == CHAOS_STONE3)
  ChaosStoneDeath(pUser);

if (GetZoneID() == ZONE_RONARK_LAND || GetZoneID() == ZONE_RONARK_LAND_BASE || GetZoneID() == ZONE_ARDREAM)
  ChaosStoneBossKilledBy();
---OnDeathProcess---
