# Raspberry Pi JSON using Python

The json library allows to parse string to JSON object.
That can be used to parse message sent via MQTT from devices.

```python
import json

data = json.loads(message)
temperature = data['message']['measurements']['temperature']
```

source: https://reqbin.com/code/python/g4nr6w3u/python-parse-json-example
