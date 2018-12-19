<p align="center"><img src="/Media/screen_capture.png" alt="like counter" height="75%" width="75%"></p>

<p align="justify">Aujourd’hui, nous réalisons un compteur de likes Facebook, Instagram et Twitter connecté en wifi. Il vous permettra d’afficher votre nombre de likes depuis votre page facebook, ainsi que votre nombre de followers instagram et twitter.</p>

### Liste de matériel :bookmark_tabs:
***
Afin de réaliser votre compteur de likes, il vous faudra :

<ul>
	<li>un <a href="https://letmeknow.fr/shop/fr/cartes-programmables/797-linknode-d1-0612409988898.html">LinkNode D1</a> (ou équivalent Arduino)</li>
	<li>une <a href="https://letmeknow.fr/shop/fr/leds/1192-matrice-de-led-rouge-32x8-8058333499505.html?search_query=matrice+led&amp;results=214">matrice LED 32x8</a> (HT1632)</li>
	<li>5 <a href="https://letmeknow.fr/shop/fr/autres-composants/96-nappe-de-jumpers-male-femelle-20cm-6915671063107.html">fils</a> connecteurs Mâle-Femelle</li>
</ul>

### Montage :wrench:
***
Connectez les 5 fils de la manière suivante :

| Matrice LED |         LinkNode D1          |
|:-----------:|:----------------------------:|
|     5v      | 5v		     		         |
|     GND     | GND					 		 |
|     CS1     | D2						     |
|     WR      | D3					 		 |
|     DATA    | D4						     |

<p align="center"> <img src="/Media/like_counter_wire.png" alt="like counter wire"></p>
<p align="justify">Si vous disposez d’une imprimante 3D, vous pouvez télécharger le fichier d’impression 3D afin de fabriquer le boîtier. Visser l’écran ainsi que le LinkNode D1 de la manière suivante :</p>
<p align="center"> <img src="/Media/IMG_20181217.jpg" alt="like counter wire"></p>

### Le code :computer:
***
<ol><li>Téléchargez la dernière version de l'<a href="https://www.arduino.cc/en/Main/Software">IDE Arduino.</a></li>
	<li>Si vous utilisez le LinkNode D1, vous allez devoir ajouter la carte dans la liste des cartes prises en charge par l'IDE Arduino. Ouvrez l'IDE, "Fichier" → "Préférences" et dans "URL de gestionnaire de cartes supplémentaires" ajouter le lien suivant :<blockquote class="wp-block-quote"><p><br><strong>http://arduino.esp8266.com/stable/package_esp8266com_index.json</strong></p></blockquote></li>
	<li>Vous&nbsp;pouvez télécharger le code du compteur de likes sur <a href="https://github.com/letmeknowFR/compteur-likes">github</a>.</li>
	<li>Déplacer les librairies téléchargées avec le compteur de likes dans votre répertoire Arduino <strong><em>/librairies</em></strong></li><p align="center"><img src="/Media/Diagram.png" alt="" class="wp-image-1869"><br><figcaption>Votre répertoire Arduino devrait ressembler à cela</figcaption></p>
	<li>Raccordez votre compteur de likes grâce à un câble USB/microUSB&nbsp; vers votre ordinateur.</li>
	<li>Ouvrez votre IDE Arduino et modifiez les lignes <strong>23-24</strong> par le nom de votre réseau wifi ainsi que le mot de passe.</li><br><p align="center"><img src="/Media/CaptureWifi.PNG" alt="" class="wp-image-1875"/></p></ol>

### Facebook
***
<ol><li>Pour lier votre compte Facebook, vous devez vous rendre sur l'<a href="https://developers.facebook.com/?locale=fr_FR">API Facebook</a> et vous identifier. (Afin de pouvoir afficher le nombre de likes sur votre page vous devez en être administrateur).</li>
	<li>Sélectionnez "Mes applications" → "Ajouter une application", nommez votre application et faites "Créer un ID d'app".</li>
	<li>Sélectionnez "Outils" → "Explorateur de l'API Graph", puis récupérez le token d'accès (Ctrl+C).</li><br><img align="center" src="/Media/Capture5.PNG" alt="" class="wp-image-1883"/><br>
	<li>Toujours dans “Outils”, sélectionnez “Outils de débug de tokens d’accès”, coller (Ctrl+v) le dans la barre associée, puis cliquez sur “Débuguer“. Des informations sur le token d’accès devrait s’afficher dont sa durée d’expiration. Par défaut il expire au bout d’une heure, pour éviter cela cliquez sur “étendre le token d’accès”. Un nouveau token d’accès vous est donné, copiez le.</li><br><figure class="wp-block-image"><img align="center" src="/Media/Capture6.PNG" alt="" class="wp-image-1884"/></figure><br>
	<li>Afin de récupérer l’ID de votre page, copiez l’url de votre page sur <a href="https://findmyfbid.com/">ce site</a> puis cliquez sur “Find numeric ID”.</li>
	<li>Ajoutez le token d’accès et votre ID de page dans le fichier like_counter.ino à la ligne <strong>25-26</strong>.</li><br><figure class="wp-block-image"><img align="center" src="/Media/Capture7.PNG" alt="" class="wp-image-1885"/></figure></ol>

### Instagram
***
<ol><li>Afin de lier votre compte Instagram, commencez par vous identifier sur la plateforme dédiée <a href="https://www.instagram.com/developer/">ici</a>.</li>
	<li>Cliquez sur "Manage Clients".</li>
	<li>Puis remplissez les champs de la manière suivante.</li><figure class="wp-block-image"><img src="/Media/Capture10.PNG" alt="" class="wp-image-1889"></figure>
	<li>Dans l'onglet "Security", décochez "Disable implicit OAuth". Puis cliquez sur "Register".</li><figure class="wp-block-image"><img src="/Media/Capture11.PNG" alt="" class="wp-image-1890"></figure>
	<li>Une fois enregistré, vous devriez pouvoir voir votre application comme ceci, et trouver votre Client ID.</li><figure class="wp-block-image"><img src="/Media/Capture12.PNG" alt="" class="wp-image-1891"></figure>
	<li>Copier / coller l’URL suivante en remplaçant “[CLIENT_ID]” par le votre dans un navigateur web : <br><blockquote class="wp-block-quote"><br><p><strong>https://instagram.com/oauth/authorize/?client_id=[CLIENT_ID]&amp;redirect_uri=http://localhost&amp;response_type=token</strong></p></blockquote></li>
	<li>vous devriez récupérer une URL de ce type : http://localhost/#access_token=<strong>**********</strong> , avec votre access token à la fin.</li>
	<li>Il ne vous restera plus qu’à l’ajouter dans le code, ligne <strong>29</strong>.</li><figure class="wp-block-image"><img src="/Media/Capture13.PNG" alt="" class="wp-image-1892"></figure></ol>

### Twitter
***
<ol><li>Pour&nbsp;lier votre compte Twitter, rien de plus simple. Récupérez votre nom de page dans l’url. (ex: <a href="https://twitter.com/letmeknowfr?lang=fr">https://twitter.com/letmeknowfr?lang=fr</a>&nbsp;→ le nom de notre Twitter est "letmeknowfr")</li>
	<li>Puis ajoutez le dans le programme du compteur ligne <strong>27</strong>.</li><figure class="wp-block-image"><img src="/Media/Capture9.PNG" alt="" class="wp-image-1902"></figure></ol>

### Téléverser le code
***
<ol><li>Afin de téléverser le code sur votre carte, commencez par sélectionner votre carte. Dans “Outils”&nbsp;→ “Type de carte”, sélectionner “WeMos D1 (Retired)” si vous utilisez le LinkNode D1. Puis paramétrer le de la manière suivante :</li><figure class="wp-block-image"><img src="/Media/Capture17.png" alt="" class="wp-image-1904"></figure>
	<li>Sélectionnez le port COM sur lequel votre carte est connectée.</li><li>Et enfin, cliquez sur <strong>Téléverser</strong>.</li><figure class="wp-block-image"><img src="/Media/Capture16.PNG" alt="" class="wp-image-1905"></figure></ol>