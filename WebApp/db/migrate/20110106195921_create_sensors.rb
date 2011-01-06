class CreateSensors < ActiveRecord::Migration
  def self.up
    create_table :sensors do |t|
		t.string :typ, :port, :station

		t.timestamps
    end
  end

  def self.down
    drop_table :sensors
  end
end
