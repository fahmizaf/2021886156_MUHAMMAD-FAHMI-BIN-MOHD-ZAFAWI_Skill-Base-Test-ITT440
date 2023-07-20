import socket

def bar_to_atmosphere(pressure):
    return pressure * 0.986923

def main():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('192.168.241.128', 2820)
    server_socket.listen(1)
    
    print("Server is listening...")
    
    while True:
        conn, addr = server_socket.accept()
        print(f"Connected by {addr}")
        
        data = conn.recv(1024)
        pressure_bar = float(data.decode())
        
        pressure_atm = bar_to_atmosphere(pressure_bar)
        
        conn.send(str(pressure_atm).encode())
        print(f"Sent atmosphere-standard value: {pressure_atm} atm")
        
        conn.close()

if __name__ == "__main__":
    main()
