import { useEffect, useState } from "react";
import { useClient } from "../helpers/client";

export default function useMessage() {
  const { json } = useClient();

  const [bedroomTemp, setBedroomTemp] = useState(null);
  const [livingRoomTemp, setLivingRoomTemp] = useState(null);
  const [bell, setBell] = useState(null);

  useEffect(() => {
    if (json) {
      console.log(json, " useMessage");
      setMessage(json);
    }
  }, [json]);

  const setMessage = (parsedMessage) => {
    if (parsedMessage.bedroomTemp !== undefined) {
      setBedroomTemp(parsedMessage.bedroomTemp);
    }
    if (parsedMessage.livingRoomTemp !== undefined) {
      setLivingRoomTemp(parsedMessage.livingRoomTemp);
    }
    if (parsedMessage.bell !== undefined) {
      setBell(parsedMessage.bell);
    }
  };

  return { bedroomTemp, livingRoomTemp, bell, setMessage };
}