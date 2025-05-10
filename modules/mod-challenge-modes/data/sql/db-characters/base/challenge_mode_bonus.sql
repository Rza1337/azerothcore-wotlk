DROP TABLE IF EXISTS boosted_characters;

CREATE TABLE boosted_characters (
    account_id INT UNSIGNED NOT NULL,
    guid INT UNSIGNED NOT NULL,
    PRIMARY KEY (account_id)
);
