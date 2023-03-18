import sqlite3
from sqlite3 import Error


def create_connection(db_file):
    """ create a database connection to SQLite database specified by bd_file
    :param db_file: database file
    :return: Connection object or None
    """
    conn = None
    try:
        conn = sqlite3.connect(db_file)
        return conn
    except Error as e:
        print(e)

    return conn


def create_table(conn, create_table_sql):
    """ create a table from create_table_sql statement
    :param conn: Connection object
    :param create_table_sql: CREATE TABLE sql statement
    :return:
    """
    try:
        cr = conn.cursor()
        cr.execute(create_table_sql)
    except Error as e:
        print(e)


def main():
    database = r"measurementsDB.db"
    _create_measurementstype_table = """CREATE TABLE IF NOT EXISTS measurementsType(
                                        idMeasurementType INTEGER PRIMARY KEY AUTOINCREMENT, 
                                        measurementType TEXT NOT NULL);"""
    _create_iothubs_table = """CREATE TABLE IF NOT EXISTS iotHubs(
                                idIotHub INTEGER PRIMARY KEY AUTOINCREMENT, 
                                iotHub TEXT NOT NULL);"""
    _create_devices_table = """CREATE TABLE IF NOT EXISTS devices(
                                idDevice INTEGER PRIMARY KEY AUTOINCREMENT, 
                                device TEXT NOT NULL, 
                                description TEXT);"""
    _create_temperature_table = """CREATE TABLE IF NOT EXISTS temperature(
                                iotHub INTEGER, 
                                idDevice INTEGER, 
                                idChannel INTEGER, 
                                value REAL NOT NULL, 
                                datetime TEXT NOT NULL, 
                                FOREIGN KEY(iotHub) REFERENCES iotHubs(idIotHub), 
                                FOREIGN KEY(idDevice) REFERENCES devices(idDevice), 
                                PRIMARY KEY (iotHub, idDevice, idChannel))"""

    conn = create_connection(database)
    if conn is not None:
        create_table(conn, _create_measurementstype_table)
        create_table(conn, _create_iothubs_table)
        create_table(conn, _create_devices_table)
        create_table(conn, _create_temperature_table)
    else:
        print("Error, cannot connect to database.")


if __name__ == '__main__':
    main()
