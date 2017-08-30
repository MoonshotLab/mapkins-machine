require('dotenv').config();

const express = require('express');
const app = express();
const path = require('path');
const bodyParser = require('body-parser');
const http = require('http').Server(app);

const dispense = require('./lib/dispense').init();

app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'pug');
app.use(express.static(path.join(__dirname, 'public')));

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));

app.get('/', (req, res) => {
  res.redirect('https://www.barkleyus.com/');
});

app.use('/status', require('./routes/status'));
app.use('/dispense', require('./routes/dispense'));
app.use('/reset', require('./routes/reset'));

require('./lib/botkit-controller')(app);

const port = process.env.PORT || 3000;
http.listen(port, () => {
  console.log('Server running on port ' + port);
});