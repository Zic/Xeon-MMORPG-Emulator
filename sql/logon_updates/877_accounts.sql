-- Expand the password field.
ALTER TABLE accounts MODIFY COLUMN password varchar(42) NOT NULL default '';
-- Set password = encrypted_password where encrypted password isn't NULL.
UPDATE accounts SET password = encrypted_password WHERE encrypted_password != '';
-- This field is no longer used.
ALTER TABLE ACCOUNTS DROP encrypted_password;