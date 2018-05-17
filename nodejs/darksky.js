require('dotenv').load();

const express = require('express');
const app = express();
const port = process.env.PORT || 8080;

const DarkSky = require('dark-sky');
const darksky = new DarkSky(process.env.DARK_SKY); // Your API KEY can be hardcoded, but I recommend setting it as an env variable.

const weatherMap = [
    {
        name: 'clear',
        conditions: ['clear-day', 'clear-night', 'wind']
    },
    {
        name: 'cloudy',
        conditions: [
            'fog',
            'cloudy',
            'partly-cloudy-day',
            'partly-cloudy-night'
        ]
    },
    {
        name: 'rainy',
        conditions: ['rain', 'snow', 'sleet', 'hail']
    }
];

const getWeather = condition =>
    weatherMap.find(weather => weather.conditions.includes(condition)).name;

app.listen(port, function() {
    console.log('Server is running on ' + port + ' port');
});

app.get('/', function(req, res) {
    res.send('da root – sandstorm');
});

app.get('/ds', function(req, res) {
    if (req.query.key === process.env.SECRET_KEY) {
        darksky
            .options({
                latitude: process.env.LAT,
                longitude: process.env.LON,
                language: 'en',
                exclude: ['currently', 'minutely', 'daily', 'alerts', 'flags']
            })
            .get()
            .then(function(data) {
                let weatherType = data.hourly.icon;
                res.send(getWeather(weatherType));
            });
    } else {
        res.send('Bad Key');
    }
    console.log(req.query.key);
    console.log(process.env.SECRET_KEY);
});
