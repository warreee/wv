import cmd

class WAXA(cmd.Cmd):
    intro = "Ward & Xavier WSN commandline tool"
    prompt = 'WAXA '

    rdf = 0

    def help_set_reduction(self):
        print('\n'.join(['set_reduction [reduction factor]',
                         'Sets the reduction factor',
        ]))

    def do_deploy(self, line):
        self.do_set_reduction()

    def calculate(self, line):
        print("Calculates the consumption en compares with standard consumption")

    def do_set_reduction(self, rdf):
        print("Give the reduction factor")
        line = input('Prompt ("stop" to quit): ')
        print(line)



if __name__ == '__main__':
    WAXA().cmdloop()