class System {
    constructor(sys_id, sys_name, proc_name, no_of_procs, clock_frequency, time_taken) {
        this.sys_id = sys_id;
        this.sys_name = sys_name;
        this.proc_name = proc_name;
        this.no_of_procs = no_of_procs;
        this.clock_frequency = clock_frequency;
        this.time_taken = time_taken;
    }
}

module.exports = System;