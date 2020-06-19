const System = require("./system");

class SystemsTable {

    constructor(dao) {
        this.dao = dao;
    }

    insert(system) {
        return this.dao.run(
            `INSERT INTO Systems VALUES (?, ?, ?, ?, ?, ?)`, [
                system.sys_id,
                system.sys_name,
                system.proc_name,
                system.no_of_procs,
                system.clock_frequency,
                system.time_taken
            ]
        );
    }

    update(clock_frequency, time_taken, sys_id) {
        return this.dao.run(
            `UPDATE Systems
            SET 
            clock_frequency = ?,
            time_taken = ?
            WHERE
            sys_id = ?`,
            [clock_frequency, time_taken, sys_id]
        );
    }

    delete(sys_id) {
        return this.dao.run(
            `DELETE FROM Systems 
            WHERE sys_id = ?`,
            [sys_id]
        );
    }

    getByID(sys_id) {
        return this.dao.get(
            `SELECT * FROM Systems
            WHERE sys_name = ?`,
            [sys_id]
        );
    }

    getAllSystems() {
        return this.dao.all(`SELECT * FROM Systems`);
    }
}

module.exports = SystemsTable;