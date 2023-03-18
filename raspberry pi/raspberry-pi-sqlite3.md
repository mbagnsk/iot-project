## Raspberry PI sqlite3

1. Before db installation update system:

```
sudo apt update
sudo apt full-upgrade
```

2. Install SQLite:

```
sudo apt install sqlite3
```

3. Creating database:

```
sqlite3 <dbName.db>
```

4. Creating table:
```
CREATE TABLE tableName(columnName type, columnName type);
```

Sources:
  - https://pimylifeup.com/raspberry-pi-sqlite/
  - https://www.sqlitetutorial.net/sqlite-python/creating-tables/
  