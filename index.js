sayThatDude('+++++++++++++++++++++++++++++++++++++++')
sayThatDude('This is from index.js')

// #region sayThatDude/print example
// for (let count = 0; count < 10; count++) {
//     sayThatDude('printing count from custom function', count)
// }
// #endregion

// #region relaxAndDoItDude example
// let interval = 0;
// let sleep = 2000
// relaxAndDoItLaterDude(sleep, interval, () => { sayThatDude('this is a callback called at ' + new Date().toISOString())  })
// // #endregionS

// #region nested relaxAndDoItDude example
let interval = 0;
let sleep = 2000
relaxAndDoItLaterDude(sleep, interval, () => {
    sayThatDude('this is a first callback called at  ' + new Date().toISOString())
    relaxAndDoItLaterDude(sleep, interval, () => {
        sayThatDude('this is a second callback called at ' + new Date().toISOString())
        relaxAndDoItLaterDude(sleep, interval, () => {
            sayThatDude('this is a third callback called at ' + new Date().toISOString())
        })
    })
})
// #endregionS

// #region setTimeout and setInterval implemntation with relaxAndDoItDude example
const setTimeout = (ms, cb) => relaxAndDoItLaterDude(ms, 0, cb);
const setInterval = (ms, cb) => relaxAndDoItLaterDude(0, ms, cb);
// #endregionS