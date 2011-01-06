class CreateSensors < ActiveRecord::Migration
  def self.up
    create_table :sensors do |t|
		t.string :port, :station, :typ
		
		t.timestamps
    end
  end

  def self.down
    drop_table :sensors
  end
end
