import React, { useState, useEffect } from 'react';
import { withStyles, makeStyles } from '@material-ui/core/styles';
import Table from '@material-ui/core/Table';
import TableBody from '@material-ui/core/TableBody';
import TableCell from '@material-ui/core/TableCell';
import TableContainer from '@material-ui/core/TableContainer';
import TableHead from '@material-ui/core/TableHead';
import TableRow from '@material-ui/core/TableRow';
import TableSortLabel from '@material-ui/core/TableSortLabel';
import Paper from '@material-ui/core/Paper';
import PropTypes from 'prop-types';
import axios from 'axios';
import CircularProgress from '@material-ui/core/CircularProgress';

const StyledTableCell = withStyles((theme) => ({
	head: {
		backgroundColor: theme.palette.info.main,
		color: theme.palette.common.white
	},
	body: {
		fontSize: 14
	}
}))(TableCell);

const StyledTableRow = withStyles((theme) => ({
	root: {
		'&:nth-of-type(odd)': {
			backgroundColor: theme.palette.action.hover
		}
	}
}))(TableRow);

const CustomStyles = makeStyles({
	table: {
		minWidth: 700
	}
});

function TableHeader(props) {
	const { order, orderBy, onReqSort } = props;
	const createSortHandler = (property) => (event) => {
		onReqSort(event, property);
	};

	const tableHeaders = [
		{ id: 'sysId', numeric: false, label: 'System Identifier' },
		{ id: 'sysName', numeric: false, label: 'System Name' },
		{ id: 'procName', numeric: false, label: 'Processor Name' },
		{ id: 'noProcs', numeric: true, label: 'No. of Processors' },
		{ id: 'clockFreq', numeric: true, label: 'Clock Freq. (MHz)' },
		{ id: 'time', numeric: true, label: 'Time Elapsed (s)' }
	];

	return (
		<TableHead>
			<StyledTableRow>
				{tableHeaders.map((tableHeader) => (
					<StyledTableCell
						key={tableHeader.id}
						align={tableHeader.numeric ? 'right' : 'left'}
						padding={false}
						sortDirection={orderBy === tableHeader.id ? order : false}
					>
						<TableSortLabel
							active={orderBy === tableHeader.id}
							direction={orderBy === tableHeader.id ? order : 'asc'}
							onClick={createSortHandler(tableHeader.id)}
						>
							{tableHeader.label}
						</TableSortLabel>
					</StyledTableCell>
				))}
			</StyledTableRow>
		</TableHead>
	);
}

TableHeader.propTypes = {
	classes: PropTypes.object.isRequired,
	onReqSort: PropTypes.func.isRequired,
	order: PropTypes.oneOf([ 'asc', 'desc' ]).isRequired,
	orderBy: PropTypes.string.isRequired
};

//compareTo similar to java function
function descendingComparator(a, b, orderBy) {
	if (b[orderBy] < a[orderBy]) {
		return -1;
	}
	if (b[orderBy] > a[orderBy]) {
		return 1;
	}
	return 0;
}

function getComparator(order, orderBy) {
	return order === 'desc'
		? (a, b) => descendingComparator(a, b, orderBy)
		: (a, b) => -descendingComparator(a, b, orderBy);
}

function sortTable(array, comparator) {
	const rowstablizer = array.map((elem, index) => [ elem, index ]);
	rowstablizer.sort((a, b) => {
		const order = comparator(a[0], b[0]);
		if (order !== 0) return order;
		return a[1] - b[1];
	});
	return rowstablizer.map((elem) => elem[0]);
}

function DisplaySortedTable() {
	const classes = CustomStyles();
	const [ order, setOrder ] = useState('asc');
	const [ orderBy, setOrderBy ] = useState('sys_name');
	const [ isLoaded, setisLoaded ] = useState(false);
	const [ benchmarks, setbenchmarks ] = useState([]);

	const handleRequestSort = (event, property) => {
		const isAsc = orderBy === property && order === 'asc';
		setOrder(isAsc ? 'desc' : 'asc');
		setOrderBy(property);
	};

	// useEffect(() => {
	// 	axios.get('https://us-central1-raytracing-2c39f.cloudfunctions.net/api/benchmarks').then((response) => {
	// 		setbenchmarks(response.data);
	// 		setisLoaded(true);
	// 	});
	// });

	useEffect(() => {
		const fetchData = async () => {
			const result = await axios.get('https://us-central1-raytracing-2c39f.cloudfunctions.net/api/benchmarks');

			setbenchmarks(result.data);
			setisLoaded(true);
		};

		fetchData();
	}, []);

	if (!isLoaded) {
		return <CircularProgress />;
	} else {
		return (
			<div className={classes.root}>
				<Paper elevation={10}>
					<TableContainer>
						<Table>
							<TableHeader
								classes={classes}
								order={order}
								orderBy={orderBy}
								onReqSort={handleRequestSort}
							/>
							<TableBody>
								{sortTable(benchmarks, getComparator(order, orderBy)).map((row, index) => {
									const labelId = `benchmark-${index}`;

									return (
										<StyledTableRow key={row.sysId}>
											<StyledTableCell component="th" scope="row" id={labelId}>
												{row.sysId}
											</StyledTableCell>
											<StyledTableCell>{row.sysName}</StyledTableCell>
											<StyledTableCell>{row.procName}</StyledTableCell>
											<StyledTableCell align="right">{parseFloat(row.noProcs)}</StyledTableCell>
											<StyledTableCell align="right">{parseFloat(row.clockFreq)}</StyledTableCell>
											<StyledTableCell align="right">{parseFloat(row.time)}</StyledTableCell>
										</StyledTableRow>
									);
								})}
							</TableBody>
						</Table>
					</TableContainer>
				</Paper>
			</div>
		);
	}
}
export default DisplaySortedTable;

/* TABLE WITHOUT SORTING FUNCTION (PRE React v16.8 IMPLEMENTATION) */

// function HeadOfTable() {
// 	const classes = CustomStyles();
// 	return (
// 		<TableContainer component={Paper}>
// 			<Table className={classes.table} aria-label="raytracing-table">
// 				<TableHead>
// 					<TableRow>
// 						<StyledTableCell>System Name</StyledTableCell>
// 						<StyledTableCell>Processor Name</StyledTableCell>
// 						<StyledTableCell align="right">No. Processors</StyledTableCell>
// 						<StyledTableCell align="right">Clock Freq.&nbsp;(Hz)</StyledTableCell>
// 						<StyledTableCell align="right">Time Elapsed&nbsp;(s)</StyledTableCell>
// 						<StyledTableCell align="right">Unique Identifier</StyledTableCell>
// 					</TableRow>
// 				</TableHead>
// 				<Table2 />
// 			</Table>
// 		</TableContainer>
// 	);
// }

// class Table2 extends React.Component {
// 	constructor(props) {
// 		super(props);
// 		this.state = {
// 			benchmarks: [],
// 			isLoaded: false
// 		};
// 	}

// 	componentDidMount() {
// 		axios.get('https://us-central1-raytracing-2c39f.cloudfunctions.net/api/benchmarks').then((result) => {
// 			this.setState({
// 				isLoaded: true,
// 				benchmarks: result.data
// 			});
// 		});
// 	}

// 	render() {
// 		const { benchmarks } = this.state;
// 		if (!this.state.isLoaded) {
// 			return <div>LOADING ...</div>;
// 		} else {
// 			return (
// 				<TableBody>
// 					{benchmarks.map((row) => (
// 						<StyledTableRow key={row.sysId}>
// 							<StyledTableCell component="th" scope="row">
// 								{row.sysName}
// 							</StyledTableCell>
// 							<StyledTableCell>{row.procName}</StyledTableCell>
// 							<StyledTableCell align="right">{row.noProcs}</StyledTableCell>
// 							<StyledTableCell align="right">{row.clockFreq}</StyledTableCell>
// 							<StyledTableCell align="right">{row.time}</StyledTableCell>
// 							<StyledTableCell align="right">{row.sysId}</StyledTableCell>
// 						</StyledTableRow>
// 					))}
// 				</TableBody>
// 			);
// 		}
// 	}
// }
