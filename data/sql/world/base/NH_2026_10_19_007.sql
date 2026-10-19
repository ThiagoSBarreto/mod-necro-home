-- Backup original values
CREATE TABLE IF NOT EXISTS skinning_loot_template_backup
LIKE skinning_loot_template;

INSERT IGNORE INTO skinning_loot_template_backup
SELECT *
FROM skinning_loot_template;

-- Double skinning drops
UPDATE skinning_loot_template AS loot
JOIN skinning_loot_template_backup AS backup
    ON loot.Entry = backup.Entry
    AND loot.Item = backup.Item
    AND loot.Reference = backup.Reference
    AND loot.LootMode = backup.LootMode
    AND loot.GroupId = backup.GroupId
SET
    loot.MinCount = backup.MinCount * 2,
    loot.MaxCount = backup.MaxCount * 2;