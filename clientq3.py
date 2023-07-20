def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('192.168.241.128', 2820))
    
    pressure_bar = input("Enter pressure in bar: ")
    
    client_socket.send(pressure_bar.encode())
    
    pressure_atm = float(client_socket.recv(1024).decode())
    
    print(f"Received atmosphere-standard value: {pressure_atm} atm")
    
    client_socket.close()

if __name__ == "__main__":
    main()
