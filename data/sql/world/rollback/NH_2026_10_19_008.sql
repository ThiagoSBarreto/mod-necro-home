START TRANSACTION;

-- =========================================================
-- Restore stack size
-- =========================================================

UPDATE item_template AS i
JOIN item_template_stack_backup AS b
    ON i.entry = b.entry
SET i.stackable = b.stackable;


-- =========================================================
-- Restore quest items drop chance
-- =========================================================

UPDATE creature_loot_template AS loot
JOIN creature_loot_template_backup AS backup
    ON loot.Entry = backup.Entry
    AND loot.Item = backup.Item
    AND loot.Reference = backup.Reference
    AND loot.LootMode = backup.LootMode
    AND loot.GroupId = backup.GroupId
SET loot.Chance = backup.Chance;


-- =========================================================
-- Restore cloths drops
-- =========================================================

UPDATE creature_loot_template AS loot
JOIN creature_loot_template_backup_cloth AS backup
    ON loot.Entry = backup.Entry
    AND loot.Item = backup.Item
    AND loot.Reference = backup.Reference
    AND loot.LootMode = backup.LootMode
    AND loot.GroupId = backup.GroupId
SET
    loot.MinCount = backup.MinCount,
    loot.MaxCount = backup.MaxCount;


-- =========================================================
-- Restore plants and minerals drop ammount
-- =========================================================

UPDATE gameobject_loot_template AS loot
JOIN gameobject_loot_template_backup_gathering AS backup
    ON loot.Entry = backup.Entry
    AND loot.Item = backup.Item
    AND loot.Reference = backup.Reference
    AND loot.LootMode = backup.LootMode
    AND loot.GroupId = backup.GroupId
SET
    loot.MinCount = backup.MinCount,
    loot.MaxCount = backup.MaxCount;


-- =========================================================
-- Restore skinning drop ammount
-- =========================================================

UPDATE skinning_loot_template AS loot
JOIN skinning_loot_template_backup AS backup
    ON loot.Entry = backup.Entry
    AND loot.Item = backup.Item
    AND loot.Reference = backup.Reference
    AND loot.LootMode = backup.LootMode
    AND loot.GroupId = backup.GroupId
SET
    loot.MinCount = backup.MinCount,
    loot.MaxCount = backup.MaxCount;

COMMIT;