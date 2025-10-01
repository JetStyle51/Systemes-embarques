# Install your WebApp React/NodeJs with OpenLiteSpeed on a VPS
## Transfer files from a computert to a VPS
📝 Requirement:

* Ton serveur VPS doit être accessible via SSH (port 22 par défaut).
- Tu dois connaître :
* l'adresse IP du serveur
* le nom d’utilisateur (souvent root par défaut)
* le mot de passe ou ta clé SSH si tu en utilises une

Transfer a file:
```bash
scp /chemin/local/fichier.txt utilisateur@ip_du_serveur:/chemin/de/destination
```
Transfer a folder:
```bash
scp -r /chemin/local/dossier utilisateur@ip_du_serveur:/chemin/de/destination
```
Example:
```bash
scp -r ~/Documents/mon-projet root@123.45.67.89:/var/www/
```
## Check the ports

```bash
sudo lsof -i -P -n | grep LISTEN
```


# Frontend

# Backend
## Start the backend as a service
`sudo systemctl restart palmbox-backend`
