// TODO: Add code to check answers to questions
let firstResult = document.querySelector("#first-result")

document.querySelectorAll("button").forEach((node) => node.addEventListener("click", (e) => {
    e.preventDefault()
    if (e.target.innerText == "1 person per 6 sheep") {
        e.target.style.backgroundColor = "lightgreen"
        firstResult.innerText = "Correct!"
        // make paragraph immutable
        firstResult = null
    }
    else if (firstResult != null) {
        e.target.style.backgroundColor = "crimson"
        firstResult.innerText = "Incorrect!"
    }
}))

let secondResult = document.querySelector("#second-result")
let secondAnswer = document.querySelector("input[type='text']")
document.querySelector("input[type='submit'").addEventListener("click", (e) => {
    if (secondAnswer.value == "Switzerland") {
        secondResult.innerText = "Correct!"
        secondAnswer.style.backgroundColor = "lightgreen"
        // make paragraph immutable
        secondResult = null
    }
    else if (secondResult != null) {
        secondResult.innerText = "Incorrect!"
        secondAnswer.style.backgroundColor = "crimson"
    }
})