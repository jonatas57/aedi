git config --local user.name jonatas57
git config --local user.email jdjonatasduarte57@gmail.com
read -p "add: " files
git add $files
read -p "commit: " msg
git commit -m $msg
