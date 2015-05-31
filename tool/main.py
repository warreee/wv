import ConfigParser

# Are set by the user:
reduction_factor = 0.0
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

def calculate():
    calculate_standard()
    calculate_improved()
    print("Calculates the consumption and compares with standard consumption")
    print("The standard energy usage is: " + str(energy_standard))
    print("The new energy usage is: " + str(energy_tot))
    energy_efficiency =  1.0 - energy_tot / energy_standard
    print("If you deploy locally on the mote the component is " + str(energy_efficiency * 100.0) +"% more efficient!")

def calculate_standard():
    energy_ant = ANT_AMPERE * ANT_VOLT * (float(bytes_per_transmission) * ANT_TIME_BYTE + ANT_TIME_START)
    global energy_standard
    energy_standard = float(energy_ant) * float(transmissions)
    # print(energy_standard)

def calculate_improved():
    energy_RAM = RAM_BYTE * float(storage)
    energy_CPU = CPU_AMPERE * float(time) * CPU_VOLT
    energy_ant = ANT_AMPERE * ANT_VOLT * (float(bytes_per_transmission) * ANT_TIME_BYTE + ANT_TIME_START)
    global reduced_transmissions
    reduced_transmissions = int(transmissions) / int(reduction_factor)
    global energy_tot
    energy_tot = energy_CPU + energy_RAM  + (energy_ant * reduced_transmissions)

def set_reduction(rdf):
    # rdf = input('Give the reduction factor: ')
    global reduction_factor
    reduction_factor = rdf
    print("The reduction factor is set to: " + str(rdf))

def set_storage(stor):
    # storage = input('Give the amount of stored bytes: ')
    global storage
    storage = stor
    print("The number of bytes stored is set to: " + str(storage))

def set_execution_time(tm):
    # time = input('Give the execution time of CPU to do computations: ')
    global time
    time = tm
    print("The execution time of the calculation is set to: " + str(time))

def set_transmissions(tms):
    # transmissions = input('Give the amount transmission/time_unit: ')
    global transmissions
    transmissions = tms
    print("The number of transmissions is set to: " + str(transmissions))

def set_bytes_per_transmission(bpt):
    # bpt = input('Give the amount bytes/transmission: ')
    global bytes_per_transmission
    bytes_per_transmission = bpt
    print("The number of bytes/transmission is set to: " + str(bpt))

if __name__ == '__main__':
    config = ConfigParser.RawConfigParser()
    config.read('parameters.cfg')
    # print config.get('sensor', 'sensor_data_size')
    set_reduction(int(config.get('reduction', 'transmit_reduction')))
    if config.get('memory', 'buffer_used') == True:
        set_storage(float(config.get('memory', 'buffer_size')))
    else:
        set_storage(0)
    set_execution_time(config.get('frequency', 'reduction_cpu_time'))
    set_transmissions(int(config.get('frequency', 'transmission_frequency')))
    set_bytes_per_transmission(int(float(config.get('sensor', 'sensor_data_size')) / float(config.get('reduction', 'data_reduction'))))
    calculate()
    raise SystemExit
