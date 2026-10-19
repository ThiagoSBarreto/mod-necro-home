-- Backup original values
CREATE TABLE IF NOT EXISTS skinning_loot_template_backup AS
SELECT Entry, Item, MinCount, MaxCount
FROM skinning_loot_template;

-- Double skinning drops
UPDATE skinning_loot_template i
JOIN skinning_loot_template_backup b on i.Entry = b.Entry AND i.Item = b.Item
SET i.MinCount = b.MinCount * 2, i.MaxCount = b.MaxCount * 2
WHERE i.Entry = b.Entry AND i.Item = b.Item;
