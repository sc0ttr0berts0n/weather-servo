require('dotenv').load();

const express = require('express');
const app = express();
const port = 8080;

const DarkSky = require('dark-sky');
const darksky = new DarkSky(process.env.DARK_SKY); // Your API KEY can be hardcoded, but I recommend setting it as an env variable.

app.listen(port, function() {
    console.log('Server is running on ' + port + ' port');
});

app.get('/', function(req, res) {
    res.send('da root – sandstorm');
});

app.get('/ds', function(req, res) {
    darksky
        .options({
            latitude: process.env.LAT,
            longitude: process.env.LON,
            language: 'en',
            exclude: ['currently', 'minutely', 'daily', 'alerts', 'flags']
        })
        .get()
        .then(function(data) {
            res.send('json is: ' + data.hourly.icon);
        });
});
