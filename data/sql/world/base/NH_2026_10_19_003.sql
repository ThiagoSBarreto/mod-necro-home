-- Backup original values
CREATE TABLE IF NOT EXISTS item_template_stack_backup
(
    entry INT UNSIGNED NOT NULL,
    stackable TINYINT NOT NULL,
    PRIMARY KEY (entry)
);

INSERT IGNORE INTO item_template_stack_backup
    (entry, stackable)
SELECT
    entry,
    stackable
FROM item_template;

-- Incress stack size to 5000
UPDATE item_template
SET stackable = 5000
WHERE stackable > 1
  AND InventoryType != 18;