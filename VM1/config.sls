# Configuration eth1
# RAPPEL: eth0 est à vagrant, ne pas y toucher

## Désactivation de network-manager
NetworkManager:
  service:
    - dead
    - enable: False
    
## Suppression de la passerelle par défaut
ip route del default:
  cmd:
    - run

##Configuration de VM1
eth1:
  network.managed:
    - enabled: True
    - type: eth
    - proto: none
    - ipaddr: 172.16.2.131
    - netmask: 28

eth2:
  network.managed:
    - enabled: True
    - type: eth
    - proto: none
    - enable_ipv4: false
    - enable_ipv6: true
    - ipv6proto: static
    - ipaddr: fc00:1234:3::1
    - netmask: 64

## Configuration de la route vers LAN2 via VM2
## Configuration de la route vers LAN3-6
routes1:
  network.routes:
    - name: eth1
    - routes:
       - name: LAN2
         ipaddr: 172.16.2.160/28
         gateway: 172.16.2.132

routes2:
   network.routes:
     - name: eth2
     - routes:
       - name: LAN1-6
         ipaddr: fc00:1234:1::/64
         gateway: fc00:1234:3::16
       - name: LAN2-6
         ipaddr: fc00:1234:2::/64
         gateway: fc00:1234:3::16
       - name: LAN4-6
         ipaddr: fc00:1234:4::/64
         gateway: fc00:1234:3::16

