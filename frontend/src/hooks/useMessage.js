import { useEffect, useState } from 'react';

export default function useMessage() {
  const [bedroomTemp, setBedroomTemp] = useState(null);
  const [livingRoomTemp, setLivingRoomTemp] = useState(null);
  const [bell, setBell] = useState(null);

  const setMessage = (parsedMessage) => {
    if (parsedMessage.room === 'bedroom') {
      setBedroomTemp(parsedMessage.temperature);
    } else if (parsedMessage.room === 'livingRoom') {
      setLivingRoomTemp(parsedMessage.temperature);
    }
    setBell(parsedMessage.bell.value);
  };

  return { bedroomTemp, livingRoomTemp, bell, setMessage };
}