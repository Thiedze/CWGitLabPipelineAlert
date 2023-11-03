# CWGitLabPipelineAlert
A good friend of mine told me that he had built a visual feedback for his device tests at work. A few moments later, I wanted my own. 

## working theory 
In my work, I work with and maintain GitLab pipelines. Therefore, in the past I created a pipeline that checks all other pipelines and sends a message to a Teams channel with the result of the check. 
To increase the pressure to fix broken pipelines, I created my own visual feedback for broken pipelines. 

To query the status of the pipeline, I call the GitLab API every 30 seconds to get the details of the last pipeline. 
The LED strip is controlled by Neopixel. 

## status interpretation
* initialize
  * the stripe gradually fills/empties in yellow
* created, runs and is scheduled
  * fade in/out in blue
* success
  * continuous in green
* failed
  * flashing in red       

## hardware
* WS2812 LED stripe
* Raspberry Pi Zero
* USB Cabel
* Power supply

## comfiguration file example
`
{
  "base_url": "gitlab.com",
  "access_token": "YOUR GITLAB PRIVATE ACCESS TOKEN",
  "project_id": "123456" 
}
`
