import sqlite3
from sqlite3 import Error

measurements_database = "measurementsDB.db"


class DatabaseManager:
    def __init__(self):
        try:
            self.conn = sqlite3.connect(measurements_database)
            self.conn.execute('pragma foreign_keys = on')
            self.conn.commit()
            self.cur = self.conn.cursor()
        except Error as e:
            print(e)

    def insert_data(self, sql_query, args=()):
        try:
            self.cur.execute(sql_query, args)
            self.conn.commit()
            return
        except Error as e:
            print(e)


def add_temperature_measurement(message_json):
    database_manager = DatabaseManager()
    _idDevice = int(message_json["message"]["device"]["idDevice"])
    _idChannel = int(message_json["message"]["device"]["idChannel"])
    _idIotHub = int(message_json["message"]["device"]["idIotHub"])
    _value = float(message_json["message"]["measurement"]["value"])
    _idUnit = int(message_json["message"]["measurement"]["idUnit"])
    _measurementDatetime = message_json["message"]["measurement"]["measurementDateTime"]
    sql_query = "INSERT INTO temperatures(idIotHub, idDevice, idChannel, value, idUnit, measurementDatetime) " \
                "VALUES(?, ?, ?, ?, ?, ?)"
    database_manager.insert_data(sql_query, [_idIotHub, _idDevice, _idChannel, _value, _idUnit, _measurementDatetime])
    del database_manager
