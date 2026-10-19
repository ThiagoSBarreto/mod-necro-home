-- Backup original values
CREATE TABLE IF NOT EXISTS creature_loot_template_backup_cloth AS
SELECT Entry, Item, MinCount, MaxCount
FROM creature_loot_template
WHERE Comment Like '%Cloth%' AND Comment NOT LIKE '%Pattern%';

-- Double cloths drop
UPDATE creature_loot_template i
JOIN creature_loot_template_backup_cloth b on i.Entry = b.Entry AND i.Item = b.Item 
SET i.MinCount = b.MinCount * 2, i.MaxCount = b.MaxCount * 2
WHERE i.Entry = b.Entry AND i.Item = b.Item;