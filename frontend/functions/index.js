// // Create and Deploy Your First Cloud Functions
// // https://firebase.google.com/docs/functions/write-firebase-functions
//

const cors = require('cors')({ origin: true });
const functions = require('firebase-functions');
const admin = require('firebase-admin');
admin.initializeApp();
const db = admin.firestore();

const express = require('express');
const app = express();

app.get('/benchmarks', (req, res) => {
	cors(req, res, () => {});
	db
		.collection('benchmarks')
		.orderBy('time', 'asc')
		.get()
		.then((data) => {
			let benchmarks = [];
			let display_data = [];
			data.forEach((doc) => {
				benchmarks.push({
					sysId: doc.id,
					sysName: doc.data().sysName,
					noProcs: doc.data().noProcs,
					time: doc.data().time,
					procName: doc.data().procName,
					clockFreq: doc.data().clockFreq,
					receipt_time: doc.data().receipt_time
				});
			});
			return res.json(benchmarks);
		})
		.catch((err) => {
			console.error(err);
			return res.status(500).json({ error: err.code });
		});
});

app.post('/benchmarks', (request, response) => {
	if (request.method !== 'POST') {
		return response.status(400).json({ error: 'Must be a POST method request.' });
	}

	const newBenchmark = {
		clockFreq: parseFloat(request.body.clockFreq),
		sysName: request.body.sysName,
		noProcs: parseFloat(request.body.noProcs),
		time: parseFloat(request.body.time),
		procName: request.body.procName,
		receipt_time: admin.firestore.Timestamp.fromDate(new Date())
	};

	db
		.collection('benchmarks')
		.add(newBenchmark)
		.then((doc) => {
			return response.json({ message: `Benchmark ${doc.id} created successfully on remote database.` });
		})
		.catch((error) => {
			response.status(500).json({ error: 'Something went wrong with pushing the data to the database.' });
			console.log(error);
		});
});

exports.api = functions.https.onRequest(app);
// exports.api = functions.region('europe-west1').https.onRequest(app);
