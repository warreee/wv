import cmd

class WAXA(cmd.Cmd):
    intro = "Ward & Xavier WSN commandline tool"
    prompt = 'WAXA '

    # Are set by the user:
    rdf = 0.0
    storage = 0.0
    time = 0.0
    transmissions = 0.0
    bytes_per_transmission = 0.0

    # Variables used internally
    RAM_BYTE = 0.0000814375075478687  #mJ
    CPU_AMPERE = 0.0037
    CPU_VOLT = 6.0
    ANT_AMPERE = 0.04
    ANT_TIME_BYTE = 0.382  #ms
    ANT_TIME_START = 113.104  #ms
    ANT_VOLT = 6.0

    energy_standard = 0.0
    energy_RAM = 0.0
    energy_CPU = 0.0
    energy_ant = 0.0
    energy_tot = 0.0
    energy_efficiency = 0.0

    reduced_transmissions = 0


    def do_exit(self, line):
        raise SystemExit

    def do_deploy(self, line):
        self.do_set_reduction(line)
        self.do_set_storage(line)
        self.do_set_execution_time(line)
        self.do_set_transmissions(line)
        self.do_set_bytes_per_transmission(line)
        self.do_calculate(line)

    def do_calculate(self, line):
        self.do_calculate_standard(line)
        self.do_calculate_opt(line)
        print("Calculates the consumption and compares with standard consumption")
        print("The standard energy usage is: " + str(self.energy_standard))
        print("The new energy usage is: " + str(self.energy_tot))
        self.energy_efficiency =  1.0 - self.energy_tot / self.energy_standard
        print("If you deploy here the component is " + str(self.energy_efficiency) +"% more efficient!")


    def do_calculate_standard(self, line):
        self.calculate_ANT()
        self.energy_standard = float(self.energy_ant) * float(self.transmissions)
        print(self.energy_standard)

    def do_calculate_opt(self, line):
        self.calculate_RAM()
        self.calculate_CPU()
        self.calculate_ANT()
        self.reduced_transmissions = int(self.transmissions) / int(self.rdf)
        self.energy_tot = self.energy_CPU + self.energy_RAM  + (self.energy_ant * self.reduced_transmissions)

    def calculate_RAM(self):
        self.energy_RAM = self.RAM_BYTE * float(self.storage)

    def calculate_CPU(self):
        self.energy_CPU = self.CPU_AMPERE * float(self.time) * self.CPU_VOLT

    def calculate_ANT(self):
        self.energy_ant = self.ANT_AMPERE * self.ANT_VOLT * (
            float(self.bytes_per_transmission) * self.ANT_TIME_BYTE + self.ANT_TIME_START)


    def do_set_reduction(self, rdf):
        if not rdf:
            rdf = input('Give the reduction factor: ')
            self.rdf = rdf
        else:
            self.rdf = rdf
        print("The reduction factor is set to: " + rdf)

    def help_set_reduction(self):
        print('\n'.join(['set_reduction [reduction factor]',
                         'Sets the reduction factor',
        ]))

    def do_set_storage(self, storage):
        if not storage:
            storage = input('Give the amount of stored bytes: ')
            self.storage = storage
        else:
            self.storage = storage
        print("The number of bytes stored is set to: " + storage)

    def do_set_execution_time(self, time):
        if not time:
            time = input('Give the execution time of CPU to do computations: ')
            self.time = time
        else:
            self.time = time
        print("The execution time of the calculation is set to: " + time)

    def do_set_transmissions(self, transmissions):
        if not transmissions:
            transmissions = input('Give the amount transmission/time_unit: ')
            self.transmissions = transmissions
        else:
            self.transmissions = transmissions
        print("The number of transmissions is set to: " + transmissions)

    def do_set_bytes_per_transmission(self, bpt):
        if not bpt:
            bpt = input('Give the amount bytes/transmission: ')
            self.bytes_per_transmission = bpt
        else:
            self.bytes_per_transmission = bpt
        print("The number of bytes/transmissions is set to: " + bpt)


if __name__ == '__main__':
    WAXA().cmdloop()
