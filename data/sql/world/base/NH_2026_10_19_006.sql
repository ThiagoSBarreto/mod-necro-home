-- Backup original values
CREATE TABLE IF NOT EXISTS gameobject_loot_template_backup_gathering
LIKE gameobject_loot_template;

INSERT IGNORE INTO gameobject_loot_template_backup_gathering
SELECT *
FROM gameobject_loot_template
WHERE Comment LIKE '%Vein%Ore'
   OR Comment LIKE '%Deposit%Ore'
   OR Comment REGEXP '^(.+) - \\1$';

-- Double Veins and Deposits drop
UPDATE gameobject_loot_template AS loot
JOIN gameobject_loot_template_backup_gathering AS backup
    ON loot.Entry = backup.Entry
    AND loot.Item = backup.Item
    AND loot.Reference = backup.Reference
    AND loot.LootMode = backup.LootMode
    AND loot.GroupId = backup.GroupId
SET
    loot.MinCount = backup.MinCount * 2,
    loot.MaxCount = backup.MaxCount * 2;