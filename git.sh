name= grep -r "name" ./.git/config | awk '{print $3}'
email= grep -r "email" ./.git/config | awk '{print $3}'
if [ "$name" -ne "jonatas57" ]; then
  git config --local user.name jonatas57
  git config --local user.email jdjonatasduarte57@gmail.com
read -p "add: " files
git add $files
read -p "commit: " msg
git commit -m $msg
git push
