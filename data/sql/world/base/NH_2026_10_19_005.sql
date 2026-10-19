-- Backup original values
CREATE TABLE IF NOT EXISTS creature_loot_template_backup_cloth
LIKE creature_loot_template;

INSERT IGNORE INTO creature_loot_template_backup_cloth
SELECT *
FROM creature_loot_template
WHERE Comment LIKE '%Cloth%'
  AND Comment NOT LIKE '%Pattern%';

-- Double cloths drop
UPDATE creature_loot_template AS loot
JOIN creature_loot_template_backup_cloth AS backup
    ON loot.Entry = backup.Entry
    AND loot.Item = backup.Item
    AND loot.Reference = backup.Reference
    AND loot.LootMode = backup.LootMode
    AND loot.GroupId = backup.GroupId
SET
    loot.MinCount = backup.MinCount * 2,
    loot.MaxCount = backup.MaxCount * 2;