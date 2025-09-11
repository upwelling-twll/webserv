#!/bin/bash

# Create directories
mkdir -p /var/www/errors \
         /var/www/uploads \
         /home/twillian/var/www \
         /usr/local/cgi-bin \
         /srv/example/site/new \
         /srv/example/site/files \
         /srv/example/site/tmp

# Create and populate files

cat <<'EOF' > /var/www/index.html
<!DOCTYPE html>
<html>
<head><title>Main Page</title></head>
<body>
<h1>Welcome to server on port 1025</h1>
<p>This is the default index page.</p>
</body>
</html>
EOF

cat <<'EOF' > /var/www/errors/generic.html
<!DOCTYPE html>
<html>
<head><title>Error Page</title></head>
<body>
<h1>Error Occurred</h1>
<p>This is the generic error page.</p>
</body>
</html>
EOF

cat <<'EOF' > /home/twillian/var/www/index.html
<!DOCTYPE html>
<html>
<head><title>/test/ Index</title></head>
<body>
<h1>/test/ Index Page</h1>
<p>This is served from <code>/home/twillian/var/www/</code></p>
</body>
</html>
EOF

cat <<'EOF' > /var/www/uploads/index.html
<!DOCTYPE html>
<html>
<head><title>Uploads</title></head>
<body>
<h1>/upload/ Directory</h1>
<p>Upload testing directory.</p>
</body>
</html>
EOF

cat <<'EOF' > /usr/local/cgi-bin/index.html
<!DOCTYPE html>
<html>
<head><title>CGI-Bin</title></head>
<body>
<h1>CGI-Bin Test</h1>
<p>This is <code>/cgi-bin/</code> default page.</p>
</body>
</html>
EOF

cat <<'EOF' > /srv/example/site/index.html
<!DOCTYPE html>
<html>
<head><title>Main Page</title></head>
<body>
<h1>Welcome to example.com on port 8080</h1>
<p>This is the default index page.</p>
</body>
</html>
EOF

cat <<'EOF' > /srv/example/site/new/index.html
<!DOCTYPE html>
<html>
<head><title>/new/ Page</title></head>
<body>
<h1>/new/ Page</h1>
<p>You should have been redirected here from <code>/old/</code>.</p>
</body>
</html>
EOF

cat <<'EOF' > /srv/example/site/files/index.html
<!DOCTYPE html>
<html>
<head><title>Files</title></head>
<body>
<h1>/files/ Directory</h1>
<p>This is the listing root for /files/</p>
</body>
</html>
EOF

cat <<'EOF' > /srv/example/site/tmp/index.html
<!DOCTYPE html>
<html>
<head><title>/tmp/ Page</title></head>
<body>
<h1>/tmp/ Page</h1>
<p>This page is under <code>/srv/example/tmp/</code></p>
</body>
</html>
EOF

echo "✅ All test pages created and populated!"
