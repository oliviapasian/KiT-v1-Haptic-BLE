let myBLE;
const SERVICE_UUID = "19b10000-e8f2-537e-4f6c-d104768a1214";
const CHARACTERISTIC_UUID = "19b10001-e8f2-537e-4f6c-d104768a1214";

let hapticCharacteristic;

function setup() {
  createCanvas(windowWidth, windowHeight);
  background('#ddb3f5');
  myBLE = new p5ble();

  let connectButton = createButton('Connect');
  connectButton.position(120, 50);
  connectButton.size(450, 100);
  connectButton.style('font-size', '45px');
  connectButton.style('background', 'white');
  connectButton.mousePressed(connectToHaptic);

  let pattern1 = createButton('Heart/Closeness');
  pattern1.position(120, 200);
  pattern1.size(450, 100);
  pattern1.style('font-size', '45px');
  pattern1.style('background', 'lightgreen');
  pattern1.mousePressed(() => sendPattern(1));

  let pattern2 = createButton('Hug/Squeeze');
  pattern2.position(120, 350);
  pattern2.size(450, 100);
  pattern2.style('font-size', '45px');
  pattern2.style('background', 'orchid');
  pattern2.mousePressed(() => sendPattern(2));

  let pattern3 = createButton('Tap/Attention');
  pattern3.position(120, 500);
  pattern3.size(450, 100);
  pattern3.style('font-size', '45px');
  pattern3.style('background', 'cornflowerblue');
  pattern3.mousePressed(() => sendPattern(3));
}

function connectToHaptic() {
  myBLE.connect(SERVICE_UUID, gotCharacteristics);
}

function gotCharacteristics(error, characteristics) {
  if (error) {
    console.error('Error:', error);
    return;
  }
  console.log('Characteristics:', characteristics);
  hapticCharacteristic = characteristics.find(c => c.uuid === CHARACTERISTIC_UUID);
}

function sendPattern(patternNum) {
  if (hapticCharacteristic) {
    myBLE.write(hapticCharacteristic, String(patternNum), "string");
    console.log(`Sent pattern ${patternNum}`);
  } else {
    console.log('Not connected yet');
  }
}
