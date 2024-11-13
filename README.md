# SmartHome
---


| Name | Ubicacion | Componente | Pin |  |
| --- | --- | --- | --- | --- |
| light-bedroom | Dormitorio | Led |  |  |
| light-livingroom | Sala | Led |  |  |
| light-bathroon | Baño | Led |  |  |
| light-kitchen | Cocina | Led |  |  |
|  |  |  |  |  |

## Mensaje de la pagina web → ESP32

---

Este es el JSON que la pagina usara para enviar los datos hacia la ESP32, los datos estan anidados de la siguiente forma, este JSON se envia usando la función publish cada que detecta que ha ocurrido un cambio, para ello se usan los estados de React JS

```json
[
  {
    "name": "bedroom",
    "light": {
      "on": true,
      "value": "102"
    },
    "temperature": 24,
    "air": {
      "on": false,
      "value": 0
    }
  },
  {
    "name": "bathroom",
    "light": {
      "on": false,
      "value": 0
    },
    "waterService": false
  },
  {
    "name": "kitchen",
    "light": {
      "on": false,
      "value": 0
    },
    "gasService": false
  },
  {
    "name": "livingRoom",
    "light": {
      "on": false,
      "value": 0
    },
    "temperature": 24,
    "air": {
      "on": false,
      "value": 0
    },
    "tv": {
      "on": false,
      "timer": 0
    },
    "door": {
      "open": false,
      "password": 1234
    },
    "bell": {
      "on": false,
      "value": 2
    }
  }
]
```

## Mensaje de la ESP32 → Página web

---

Este JSON en la información que mandará la ESP32 a nuestra pagina web, los datos son solo mediciones de temperatura y el timbre por proximidad, estos mensajes de enviar periodicamente.

```json
{
	"bedroomTemp":6,
	"livingRoomTemp":3,
	"bell": 2
}
```
