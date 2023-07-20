import socket
import threading
import random

QUOTES = [
    "Success is no accident. It is hard work, perseverance, learning, studying, sacrifice, and most of all, love of what you are doing or learning to do. - Pelé”,

"The more difficult the victory, the greater the happiness in winning. - Pelé”,

"Football is like life - it requires perseverance, self-denial, hard work, sacrifice, dedication, and respect for authority. - Vince Lombardi”,

"The rules of soccer are very simple, basically it is this: if it moves, kick it. If it doesn't move, kick it until it does. - Phil Woosnam”,

"Success is not just about winning. It's about getting better every day, working hard, and creating a legac. - Mia Hamm”,

"I don't want to be remembered as the man who scored the most goals. I want to be remembered as the man who did everything for his team to win. - Cristiano Ronaldo”,

"Some people believe football is a matter of life and death. I can assure you it is much, much more important than that. - Bill Shankly”,
]

def handle_client(client_socket):
    quote = random.choice(QUOTES)
    client_socket.send(quote.encode())
    client_socket.close()

def main():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 8888))
    server_socket.listen(5)

    print("Quote of the Day server is listening...")

    while True:
        client_socket, client_addr = server_socket.accept()
        print(f"Connection from: {client_addr[0]}:{client_addr[1]}")

        client_handler = threading.Thread(target=handle_client, args=(client_socket,))
        client_handler.start()

if __name__ == "__main__":
    main()

