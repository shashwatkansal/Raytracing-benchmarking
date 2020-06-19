const Promise = require('bluebird');
const Dao = require('./dao');
const System = require('./system');
const SystemsTable = require('./systems-table');
const {
    resolve
} = require('bluebird');

function main() {
    const dao = new Dao('./systems.db');
    const sys_table = new SystemsTable(dao);

    const system = new System('ABCD12', 'test-sytem', 'test-proc', 4, 12, 60);

    

    return sys_table.getAllSystems()
        .then((rows) => {

            return new Promise((resolve, reject) => {
                rows.forEach((row) => {
                    console.log(`\n sys_id = ${row.SYS_ID}`);
                });
            });
        })
        .catch((err) => {
            console.log(err);
        });
}

main();