import network
import espnow

# A WLAN interface must be active to send()/recv()
sta = network.WLAN(network.WLAN.IF_STA)  # Or network.WLAN.IF_AP
sta.active(True)
sta.disconnect()      # For ESP8266

esp_agent = espnow.ESPNow()
esp_agent.active(True)

peers = {
    'CHRISTIAN': b'\x3c\x8a\x1f\xd5\x3f\x48',
    'ALI': b'\x7c\x9e\xbd\x6f\x71\x6c'
}

for peer_name in peers:
    esp_agent.add_peer(peers[peer_name])

msgs = []
#msgs = list(peers.keys())
while len(msgs) < 2:
    msg = esp_agent.recv(100)
    if msg[0] is not None and msg not in msgs:
        msgs.append(msg)
        print(msg)
    for peer_name in peers:
        esp_agent.send(peers[peer_name], b'NIGINI', False)
