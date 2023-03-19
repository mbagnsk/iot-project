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
    """
    try:
        cr = conn.cursor()
        cr.execute(create_table_sql)
    except Error as e:
        print(e)


def insert_data(conn, insert_statement):
    """ insert data indicated in insert_statement
    :param conn: Connection object
    :param insert_statement: INSERT INTO sql statement
    """
    try:
        cr = conn.cursor()
        cr.execute(insert_statement)
        conn.commit()
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
                                idIotHub INTEGER NOT NULL, 
                                idDevice INTEGER NOT NULL, 
                                idChannel INTEGER NOT NULL,
                                value REAL NOT NULL, 
                                datetime TEXT NOT NULL, 
                                FOREIGN KEY(idIotHub) REFERENCES iotHubs(idIotHub), 
                                FOREIGN KEY(idDevice) REFERENCES devices(idDevice), 
                                PRIMARY KEY (idIotHub, idDevice, idChannel))"""
    _create_units_table = """CREATE TABLE IF NOT EXISTS units(
                            idUnit INTEGER PRIMARY KEY AUTOINCREMENT,
                            idMeasurementType INTEGER NOT NULL,
                            unitName TEXT NOT NULL,
                            unit TEXT NOT NULL,
                            FOREIGN KEY(idMeasurementType) REFERENCES measurementsType(idMeasurementType));"""

    _insert_measurementtype_init = """INSERT INTO measurementsType (measurementType) VALUES('temperature');"""
    _insert_iothub_init = """INSERT INTO iotHubs (iotHub) VALUES ('Raspberry Pi 3B');"""
    _insert_devices_init = """INSERT INTO devices (device) VALUES ('ESP8266');"""
    _insert_units_init = """INSERT INTO units (idMeasurementType, unitName, unit) VALUES(1, 'Celsius', 'C');"""

    conn = create_connection(database)
    if conn is not None:
        create_table(conn, _create_measurementstype_table)
        create_table(conn, _create_iothubs_table)
        create_table(conn, _create_devices_table)
        create_table(conn, _create_temperature_table)
        create_table(conn, _create_units_table)
        insert_data(conn, _insert_measurementtype_init)
        insert_data(conn, _insert_iothub_init)
        insert_data(conn, _insert_devices_init)
        insert_data(conn, _insert_units_init)
    else:
        print("Error, cannot connect to database.")


if __name__ == '__main__':
    main()
