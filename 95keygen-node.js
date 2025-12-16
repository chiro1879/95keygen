const MAX_ARR_SIZE = 14282;

function padNumberWithZeros(num, desiredLength) {
    let temp = num.toString();
    let len = temp.length;
    let zeros = desiredLength - len;
    let buffer = '0'.repeat(zeros) + temp;
    return buffer;
}

function rnd(min, max) {
    return Math.floor(Math.random() * (max - min)) + min;
}

console.log("Calculating...");

let arr = new Array(MAX_ARR_SIZE);
let arrCount = 0;

for (let i = 0; i < 100000; i++) {
    let numStr = padNumberWithZeros(i, 5);

    let sum = 0;
    for (let j = 0; j < 5; j++) {
        sum += parseInt(numStr[j]);
    }

    if (sum % 7 === 0) {
        if (arrCount < MAX_ARR_SIZE) {
            arr[arrCount++] = numStr;
        }
    }

    if (i % 1000 === 0) {
        console.log(`Calculating...\n ${Math.floor((i * 100) / 100000)}%`);
    }
}

const one = padNumberWithZeros(rnd(1, 366), 3);
const two = padNumberWithZeros(rnd(95, 99), 2);

if (arrCount === 0) {
    console.log("No valid serial parts found.");
    process.exit(1);
}

const three = arr[rnd(0, arrCount)];
const four = arr[rnd(0, arrCount)];

const key = `${one}${two}-OEM-00${three}-${four}`;
console.log(key);